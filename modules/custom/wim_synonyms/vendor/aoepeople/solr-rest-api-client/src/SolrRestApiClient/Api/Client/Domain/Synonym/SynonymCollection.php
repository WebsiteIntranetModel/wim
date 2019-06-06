<?php

namespace SolrRestApiClient\Api\Client\Domain\Synonym;
use SolrRestApiClient\Api\Client\Domain\AbstractCollection;
use Traversable;

/**
 * Class SynonymCollection
 *
 * @author Timo Schmidt <timo.schmidt@aoe.com>
 * @package SolrRestApiClient\Api\Client\Domain\Synonym
 */
class SynonymCollection extends AbstractCollection {

	/**
	 * @param Synonym $synonym
	 */
	public function add(Synonym $synonym) {
		$this->data->append($synonym);
	}

	/**
	 * @param $index
	 * @return mixed
	 */
	public function getByIndex($index) {
		return $this->data->offsetGet($index);
	}
}