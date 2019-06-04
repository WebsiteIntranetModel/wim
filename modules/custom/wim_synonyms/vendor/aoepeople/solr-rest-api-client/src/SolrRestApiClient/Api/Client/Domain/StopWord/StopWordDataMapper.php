<?php

namespace SolrRestApiClient\Api\Client\Domain\StopWord;

use SolrRestApiClient\Api\Client\Domain\JsonDataMapperInterface;
use SolrRestApiClient\Api\Client\Domain\StopWord\StopWordCollection;

/**
 * Class StopWordDataMapper
 *
 * Reconstitutes the json response to a StopWord object.
 *
 * @author Timo Schmidt <timo.schmidt@aoe.com>
 * @package SolrRestApiClient\Api\Client\Domain\StopWord
 */
class StopWordDataMapper implements JsonDataMapperInterface {

	/**
	 * @param string $json
	 * @return StopWordCollection
	 */
	public function fromJson($json) {
		$stopWordCollection = new StopWordCollection();
		$object = json_decode($json);

		if (!is_object($object) || !isset($object->wordSet->managedList)) {
			return $stopWordCollection;
		}

		$mapping = $object->wordSet->managedList;
		foreach ($mapping as $word) {
			$stopWord = new StopWord();
			$stopWord->setWord($word);

			$stopWordCollection->add($stopWord);
		}

		return $stopWordCollection;
	}

	/**
	 * @param StopWordCollection $stopWordCollection
	 * @return string
	 */
	public function toJson($stopWordCollection) {
		$result = array();

		/** @var $stopWordCollection StopWordCollection */
		foreach($stopWordCollection as $stopWord) {
			/** @var $stopWord StopWord */
			$result[] = $stopWord->getWord();
		}

		return json_encode($result);
	}
}
