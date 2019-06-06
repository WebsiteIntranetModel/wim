<?php

namespace SolrRestApiClient\Api\Client\Domain;

/**
 * Class AbstractCollection
 *
 * @author Timo Schmidt <timo.schmidt@aoe.com>
 * @package SolrRestApiClient\Api\Client\Domain
 */
abstract class AbstractCollection implements \IteratorAggregate {

	/**
	 * @var \ArrayObject
	 */
	protected $data;

	public function __construct() {
		$this->data = new \ArrayObject();
	}

	/**
	 * (PHP 5 &gt;= 5.0.0)<br/>
	 * Retrieve an external iterator
	 * @link http://php.net/manual/en/iteratoraggregate.getiterator.php
	 * @return \Traversable An instance of an object implementing <b>Iterator</b> or
	 * <b>Traversable</b>
	 */
	public function getIterator() {
		return $this->data->getIterator();
	}

	/**
	 * @return int
	 */
	public function getCount() {
		return $this->data->count();
	}

	/**
	 * @return array
	 */
	public function toArray() {
		return $this->data->getArrayCopy();
	}
}