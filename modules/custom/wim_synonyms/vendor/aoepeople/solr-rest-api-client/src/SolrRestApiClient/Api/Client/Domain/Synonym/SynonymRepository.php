<?php

namespace SolrRestApiClient\Api\Client\Domain\Synonym;
use SolrRestApiClient\Api\Client\Domain\AbstractRepository;
use SolrRestApiClient\Api\Client\Domain\AbstractTaggedResourceRepository;

/**
 * Repository to handle synonyms in solr using the RestAPI
 *
 * @author Timo Schmidt <timo.schmidt@aoe.com>
 */
class SynonymRepository extends AbstractTaggedResourceRepository {

	/**
	 * @var string
	 */
	protected $restEndPointPath = 'schema/analysis/synonyms/';

	/**
	 * @param SynonymDataMapper $dataMapper
	 */
	public function injectDataMapper(SynonymDataMapper $dataMapper) {
		$this->dataMapper = $dataMapper;
	}

	/**
	 * @param SynonymCollection $synonyms
	 * @param $forceResourceTag
	 * @return bool
	 */
	public function addAll(SynonymCollection $synonyms, $forceResourceTag = null) {
		$resourceTag    = $this->getTag($forceResourceTag);
		$json           = $this->dataMapper->toJson($synonyms);
		$endpoint       = $this->getEndpoint(array($resourceTag));
		$response       = $this->executePostRequest($endpoint, $json);

		return $response->getStatusCode() == 200;
	}

	/**
	 * @param $forceResourceTag
	 * @return SynonymCollection
	 */
	public function getAll($forceResourceTag = null) {
		try {
			$resourceTag    = $this->getTag($forceResourceTag);
			$endpoint       = $this->getEndpoint(array($resourceTag));
			$response       = $this->executeGetRequest($endpoint);
			$result         = $response->getBody(true);
		} catch ( \Guzzle\Http\Exception\BadResponseException $e) {
			if($e->getResponse()->getStatusCode() === 404) {
				return new SynonymCollection();
			}
		}

		return $this->dataMapper->fromJson($result);
	}

	/**
	 * @param string $mainWord
	 * @param string $forceResourceTag
	 * @return SynonymCollection
	 */
	public function getByMainWord($mainWord = '', $forceResourceTag = null) {
		$resourceTag    = $this->getTag($forceResourceTag);
		$endpoint       = $this->getEndpoint(array($resourceTag));

		if(trim($mainWord) != '') {
			$endpoint = $endpoint . '/' .$mainWord;
		}

		$response = $this->executeGetRequest($endpoint);
		$result = $response->getBody(true);

		return $this->dataMapper->fromJsonToMainWordCollection($result, $mainWord, $forceResourceTag);
	}

	/**
	 * @param string $forceResourceTag
	 * @return bool
	 * @throws \Exception
	 */
	public function deleteAll($forceResourceTag = null) {
		$result                 = array();
		$resourceTag            = $this->getTag($forceResourceTag);
		$synonymsCollection     = $this->getAll($resourceTag);

		foreach($synonymsCollection->toArray() as $synonymObject) {
			$result[] = $synonymObject->getMainWord();
		}

		if(count($result) > 0) {
			foreach($result as $mainWord) {
				$endpoint = $this->getEndpoint(array($resourceTag, $mainWord));
				$response = $this->executeDeleteRequest($endpoint);
				if($response->getStatusCode() != 200 ) {
					throw new \Exception($mainWord . " do not exists.");
				}
			}
		}
		return true;
	}

	/**
	 * @param string $mainWord
	 * @param string $forceResourceTag
	 * @return bool
	 * @throws \Exception
	 */
	public function deleteByMainWord($mainWord, $forceResourceTag = null) {
		try {
			$resourceTag    = $this->getTag($forceResourceTag);
			$endpoint       = $this->getEndpoint(array($resourceTag, $mainWord));
			$this->executeDeleteRequest($endpoint);
			return true;
		} catch(\Exception $e) {
			var_dump($e->getMessage());
		}
	}
}