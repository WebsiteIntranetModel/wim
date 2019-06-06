<?php

namespace SolrRestApiClient\Api\Client\Domain\Schema\Field;

use SolrRestApiClient\Api\Client\Domain\AbstractCollection;

/**
 * Class FieldCollection
 *
 * @author Timo Schmidt <timo.schmidt@aoe.com>
 * @package SolrRestApiClient\Api\Client\Domain\StopWord
 */
class FieldCollection extends AbstractCollection {

	/**
	 * @param AbstractField $field
	 */
	public function add(AbstractField $field) {
		$this->data->append($field);
	}

	/**
	 * @return FieldCollection
	 */
	public function getDynamicFields() {
		$result = new FieldCollection();
		foreach($this as $field) {
			if($field instanceof DynamicField) {
				$result->add($field);
			}
		}

		return $result;
	}

	/**
	 * @return FieldCollection
	 */
	public function getStaticFields() {
		$result = new FieldCollection();
		foreach($this as $field) {
			if($field instanceof StaticField) {
				$result->add($field);
			}
		}

		return $result;
	}

	/**
	 * @return int
	 */
	public function getIsIndexedCount() {
		$indexedCount = 0;

		foreach($this as $field) {
			/** @var $field AbstractField */
			if($field->getIsIndexed()) {
				$indexedCount++;
			}
		}

		return $indexedCount;
	}

	/**
	 * @return int
	 */
	public function getIsStoredCount() {
		$storedCount = 0;

		foreach($this as $field) {
			/** @var $field AbstractField */
			if($field->getIsStored()) {
				$storedCount++;
			}
		}

		return $storedCount;
	}

	/**
	 * @return int
	 */
	public function getIsMultiValuedCount() {
		$multiValuedCount = 0;

		foreach($this as $field) {
			/** @var $field AbstractField */
			if($field->getIsMultiValued()) {
				$multiValuedCount++;
			}
		}

		return $multiValuedCount;
	}

}