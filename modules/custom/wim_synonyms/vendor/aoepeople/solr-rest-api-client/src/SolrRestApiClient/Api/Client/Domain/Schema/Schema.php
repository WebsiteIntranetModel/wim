<?php

namespace SolrRestApiClient\Api\Client\Domain\Schema;

use SolrRestApiClient\Api\Client\Domain\Schema\Field\AbstractField;
use SolrRestApiClient\Api\Client\Domain\Schema\Field\FieldCollection;

class Schema {

	/**
	 * @var FieldCollection
	 */
	protected $fields;

	/**
	 *
	 */
	public function __construct() {
		$this->fields = new FieldCollection();
	}

	/**
	 * @param AbstractField $field
	 */
	public function addField(AbstractField $field) {
		$this->fields->add($field);
	}

	/**
	 * @param $name
	 */
	public function getFieldByName($name) {

	}

	/**
	 * @return FieldCollection
	 */
	public function getAllFields() {
		return $this->fields;
	}

	/**
	 * @return FieldCollection
	 */
	public function getStaticFields() {
		return $this->fields->getStaticFields();
	}

	/**
	 * @return FieldCollection
	 */
	public function getDynamicFields() {
		return $this->fields->getDynamicFields();
	}
}