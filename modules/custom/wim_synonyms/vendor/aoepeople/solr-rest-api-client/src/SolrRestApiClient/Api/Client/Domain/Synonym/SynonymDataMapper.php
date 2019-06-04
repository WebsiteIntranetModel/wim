<?php

namespace SolrRestApiClient\Api\Client\Domain\Synonym;

use SolrRestApiClient\Api\Client\Domain\JsonDataMapperInterface;

/**
 * Class SynonymDataMapper
 *
 * Reconstitutes the json response to a synonym object.
 *
 * @author Timo Schmidt <timo.schmidt@aoe.com>
 * @package SolrRestApiClient\Api\Client\Domain\Synonym
 */
class SynonymDataMapper implements JsonDataMapperInterface {

	/**
	 * @param string $json
	 * @param string $mainWord
	 * @return SynonymCollection $synonymCollection
	 */
	public function fromJson($json, $mainWord = '') {
		$synonymCollection      = new SynonymCollection();
		$object                 = json_decode($json);

		if( !is_object($object) || !isset($object->synonymMappings->managedMap) || !is_object($object->synonymMappings->managedMap)) {
			return $synonymCollection;
		}

		$mapping = $object->synonymMappings->managedMap;
		foreach($mapping as $mainWord => $wordsWithSameMeaning) {
			$synonym = new Synonym();
			$synonym->setMainWord($mainWord);

			if(!is_array($wordsWithSameMeaning)) { continue; }
			foreach($wordsWithSameMeaning as $wordWithSameMeaning) {
				$synonym->addWordsWithSameMeaning($wordWithSameMeaning);
			}
			$synonymCollection->add($synonym);
		}
		return $synonymCollection;
	}

	/**
	 * Converts a SynonymCollection to a json structure that is understood by the solr restApi.
	 *
	 * @param SynonymCollection $synonymCollection
	 * @return string
	 */
	public function toJson($synonymCollection) {
		$result =  new \StdClass();

		foreach($synonymCollection as $synonym) {
				/** @var $synonym Synonym */
			$mainWord = $synonym->getMainWord();
			$result->$mainWord = array_values($synonym->getWordsWithSameMeaning());
		}
		return json_encode($result);
	}

	/**
	 * Convert from json returned by solr restAPI from searching by synonym word
	 *
	 * @param string $json
	 * @param string $mainWord
	 * @param string $tag
	 * @return SynonymCollection
	 */
	public function fromJsonToMainWordCollection($json, $mainWord = '', $tag = '') {
		$synonymCollection = new SynonymCollection();
		$object = json_decode($json);

		if (!is_object($object) || !isset($object->$mainWord) || count($object->$mainWord) == 0) {
			return $synonymCollection;
		}

		$synonym = new Synonym();
		$synonym->setMainWord($mainWord);
		$synonym->setTag($tag);

		foreach ($object->$mainWord as $wordWithSameMeaning) {
			$synonym->addWordsWithSameMeaning($wordWithSameMeaning);
		}
		$synonymCollection->add($synonym);

		return $synonymCollection;
	}
}