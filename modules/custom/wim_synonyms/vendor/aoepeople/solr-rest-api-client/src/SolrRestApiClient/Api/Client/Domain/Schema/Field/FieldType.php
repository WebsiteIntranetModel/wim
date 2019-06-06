<?php

namespace SolrRestApiClient\Api\Client\Domain\Schema\Field;

/**
 * Class FieldType
 *
 * @author Timo Schmidt <timo.schmidt@gmx.net>
 * @package SolrRestApiClient\Api\Client\Domain\Schema
 */
class FieldType {

	/**
	 * @var string
	 */
	protected $typeName = '';

	/**
	 * @var string
	 */
	protected $class = '';

	/**
	 * @return string
	 */
	public function getClass() {
		return $this->class;
	}

	/**
	 * @param string $class
	 */
	public function setClass($class) {
		$this->class = $class;
	}

	/**
	 * @return string
	 */
	public function getTypeName() {
		return $this->typeName;
	}

	/**
	 * @param string $typeName
	 */
	public function setTypeName($typeName) {
		$this->typeName = $typeName;
	}
}