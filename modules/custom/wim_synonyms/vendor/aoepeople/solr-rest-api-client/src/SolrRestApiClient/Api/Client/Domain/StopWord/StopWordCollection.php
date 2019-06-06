<?php

namespace SolrRestApiClient\Api\Client\Domain\StopWord;

use SolrRestApiClient\Api\Client\Domain\AbstractCollection;

/**
 * Class StopWordCollection
 *
 * @author Timo Schmidt <timo.schmidt@aoe.com>
 * @package SolrRestApiClient\Api\Client\Domain\StopWord
 */
class StopWordCollection extends AbstractCollection {

	/**
	 * @param StopWord $stopWord
	 */
	public function add(StopWord $stopWord) {
		$this->data->append($stopWord);
	}

	/**
	 * @param $index
	 * @return mixed
	 */
	public function getByIndex($index) {
		return $this->data->offsetGet($index);
	}
}