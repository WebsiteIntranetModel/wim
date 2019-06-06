<?php

namespace SolrRestApiClient\Api\Client\Domain\Schema;

use Guzzle\Http\StaticClient;
use SolrRestApiClient\Api\Client\Domain\JsonDataMapperInterface;
use SolrRestApiClient\Api\Client\Domain\Schema\Field\AbstractField;
use SolrRestApiClient\Api\Client\Domain\Schema\Field\DynamicField;
use SolrRestApiClient\Api\Client\Domain\Schema\Field\StaticField;
use SolrRestApiClient\Api\Client\Domain\Schema\Schema;

/**
 * Class SchemaDataMapper
 *
 * Reconstitutes the json response to a Schema object.
 *
 * @author Timo Schmidt <timo.schmidt@aoe.com>
 * @package SolrRestApiClient\Api\Client\Domain\Schema
 */
class SchemaDataMapper implements JsonDataMapperInterface {

	/**
	 * @param $json
	 * @return Schema
	 */
	public function fromJson($json) {
		$schema     = new Schema();

		$jsonResult = json_decode($json);

		if(!isset($jsonResult->schema)) {
			return $schema;
		}

		$this->handleStaticFields($jsonResult, $schema);
		$this->handleDynamicFields($jsonResult, $schema);

		return $schema;
	}

	/**
	 * @param $object
	 * @return string
	 */
	public function toJson($object) {
		// TODO: Implement toJson() method.
	}

	/**
	 * @param $jsonResult
	 * @param $schema
	 */
	protected function handleDynamicFields($jsonResult, $schema) {
		if (isset($jsonResult->schema->dynamicFields)) {
			foreach ($jsonResult->schema->dynamicFields as $field) {
				if (!isset($field->name)) {
					throw new \InvalidArgumentException("Try to restore field without a name.");
				}

				$fieldObject = new DynamicField();
				$this->assignCommonFieldProperties($fieldObject, $field);
				$schema->addField($fieldObject);
			}
		}
	}

	/**
	 * @param $jsonResult
	 * @param $schema
	 */
	protected function handleStaticFields($jsonResult, $schema) {
		if (isset($jsonResult->schema->fields)) {
			foreach ($jsonResult->schema->fields as $field) {
				if (!isset($field->name)) {
					throw new \InvalidArgumentException("Try to restore field without a name.");
				}

				$fieldObject = new StaticField();
				$this->assignCommonFieldProperties($fieldObject, $field);
				$schema->addField($fieldObject);
			}
		}
	}

	/**
	 * @param AbstractField $fieldObject
	 * @param $field
	 */
	protected function assignCommonFieldProperties(AbstractField $fieldObject, $field) {
		$fieldObject->setName($field->name);

		if (isset($field->indexed) && $field->indexed === true) {
			$fieldObject->setIsIndexed(true);
		}

		if (isset($field->stored) && $field->stored === true) {
			$fieldObject->setIsStored(true);
		}

		if (isset($field->type)) {
			$fieldObject->setTypeName(trim($field->type));
		}

		if (isset($field->multiValued) && $field->multiValued === true) {
			$fieldObject->setIsMultiValued(true);
		}
	}
}