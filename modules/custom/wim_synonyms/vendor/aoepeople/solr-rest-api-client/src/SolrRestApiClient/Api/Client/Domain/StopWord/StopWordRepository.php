<?php

namespace SolrRestApiClient\Api\Client\Domain\StopWord;

use SolrRestApiClient\Api\Client\Domain\AbstractRepository;
use SolrRestApiClient\Api\Client\Domain\AbstractTaggedResourceRepository;

/**
 * Repository to handle StopWord in solr using the RestAPI
 * @package SolrRestApiClient\Api\Client\Domain\StopWord
 *
 * @author Timo Schmidt <timo.schmidt@aoe.com>
 */
class StopWordRepository extends AbstractTaggedResourceRepository {

	/**
	 * @var string
	 */
	protected $restEndPointPath = 'schema/analysis/stopwords/';

	/**
	 * @param StopWordDataMapper $dataMapper
	 */
	public function injectDataMapper(StopWordDataMapper $dataMapper) {
		$this->dataMapper = $dataMapper;
	}

	/**
	 * @param StopWordCollection $stopWords
	 * @param string $forceResourceTag
	 * @return bool
	 */
	public function addAll(StopWordCollection $stopWords, $forceResourceTag = null) {
		$resourceTag    = $this->getTag($forceResourceTag);
		$json           = $this->dataMapper->toJson($stopWords);
		$endpoint       = $this->getEndpoint(array($resourceTag));
		$response       = $this->executePostRequest($endpoint, $json);

		return $response->getStatusCode() == 200;
	}

	/**
	 * @param string $forceResourceTag
	 * @return StopWordCollection
	 */
	public function getAll($forceResourceTag = null) {
		try {
			$resourceTag    = $this->getTag($forceResourceTag);
			$endpoint       = $this->getEndpoint(array($resourceTag));
			$response       = $this->executeGetRequest($endpoint);
			$result         = $response->getBody(true);
		} catch ( \Guzzle\Http\Exception\BadResponseException $e) {
			if($e->getResponse()->getStatusCode() === 404) {
				return new StopWordCollection();
			}
		}

		return $this->dataMapper->fromJson($result);
	}

	/**
	 * Test to see if a specific word exists
	 *
	 * @param string $word
	 * @param string $forceResourceTag
	 * @return StopWordCollection
	 */
	public function getByWord($word = '', $forceResourceTag = null) {
		$stopwordCollection = new StopWordCollection();

		try {
			$resourceTag    = $this->getTag($forceResourceTag);
			$endpoint       = $this->getEndpoint(array($resourceTag));

			if(trim($word) != '') {
				$endpoint = $endpoint . '/' .$word;
			}

			$response = $this->executeGetRequest($endpoint);

			if($response->getStatusCode() == 200) {
				$stopWord = new StopWord();
				$stopWord->setWord($word);
				$stopWord->setTag($resourceTag);

				$stopwordCollection->add($stopWord);
			}
		} catch (\Guzzle\Http\Exception\BadResponseException $e) {
			if($e->getResponse()->getStatusCode() === 404) {
				return $stopwordCollection;
			}
		}

		return $stopwordCollection;
	}

	/**
	 * @param string $forceResourceTag
	 * @return bool
	 * @throws \Exception
	 */
	public function deleteAll($forceResourceTag = null) {
		$result                 = array();
		$resourceTag            = $this->getTag($forceResourceTag);
		$stopwordCollection     = $this->getAll($resourceTag);

		foreach($stopwordCollection->toArray() as $stopwordObject) {
			$result[] = $stopwordObject->getWord();
		}

		if(count($result) > 0) {
			foreach($result as $word) {
				$endpoint = $this->getEndpoint(array($resourceTag, $word));
				$response = $this->executeDeleteRequest($endpoint);
				if($response->getStatusCode() != 200 ) {
					throw new \Exception($word . " do not exists.");
				}
			}
		}
		return true;
	}

	/**
	 * @param string $word
	 * @param string $forceResourceTag
	 * @return bool
	 * @throws \Exception
	 */
	public function deleteByWord($word, $forceResourceTag = null) {
		try {
			$resourceTag    = $this->getTag($forceResourceTag);
			$endpoint       = $this->getEndpoint(array($resourceTag, $word));
			$this->executeDeleteRequest($endpoint);
			return true;
		} catch(\Exception $e) {
			throw new \Exception($e->getMessage() . " cant delete stopword");
		}
	}
}