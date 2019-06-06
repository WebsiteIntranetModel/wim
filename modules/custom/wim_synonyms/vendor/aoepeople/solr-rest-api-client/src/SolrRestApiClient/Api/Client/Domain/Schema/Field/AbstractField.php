<?php

namespace SolrRestApiClient\Api\Client\Domain\Schema\Field;

/**
 * Class AbstractField
 *
 * @author Timo Schmidt <timo.schmidt@gmx.net>
 * @package SolrRestApiClient\Api\Client\Domain\Schema
 */
abstract class AbstractField {

	/**
	 * @var string
	 */
	protected $name = '';

	/**
	 * @var string
	 */
	protected $typeName = '';

	/**
	 * @var boolean
	 */
	protected $isIndexed = false;

	/**
	 * @var boolean
	 */
	protected $isStored = false;

	/**
	 * @var boolean
	 */
	protected $isMultiValued = false;

	/**
	 * @return boolean
	 */
	public function getIsIndexed() {
		return $this->isIndexed;
	}

	/**
	 * @param boolean $isIndexed
	 */
	public function setIsIndexed($isIndexed) {
		$this->isIndexed = $isIndexed;
	}

	/**
	 * @return boolean
	 */
	public function getIsMultiValued() {
		return $this->isMultiValued;
	}

	/**
	 * @param boolean $isMultiValued
	 */
	public function setIsMultiValued($isMultiValued) {
		$this->isMultiValued = $isMultiValued;
	}

	/**
	 * @return boolean
	 */
	public function getIsStored() {
		return $this->isStored;
	}

	/**
	 * @param boolean $isStored
	 */
	public function setIsStored($isStored) {
		$this->isStored = $isStored;
	}

	/**
	 * @return string
	 */
	public function getName() {
		return $this->name;
	}

	/**
	 * @param string $name
	 */
	public function setName($name) {
		$this->name = $name;
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
