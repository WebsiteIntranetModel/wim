<?php

namespace SolrRestApiClient\Tests\Api\Client\Domain\Synonym;

use SolrRestApiClient\Api\Client\Domain\Schema\Field\DynamicField;
use SolrRestApiClient\Tests\BaseTestCase;

/**
 * Class DynamicFieldTestCase
 * @package SolrRestApiClient\Tests\Api\Client\Domain\Synonym
 */
class DynamicFieldTestCase extends BaseTestCase {

	/**
	 * @var DynamicField
	 */
	protected $dynamicField;

	/**
	 * @return void
	 */
	public function setUp() {
		$this->dynamicField = new DynamicField();
	}

	/**
	 * @return array
	 */
	public function getIsNameMatchingDataProvider() {
		return array(
			array(
				'configuredFieldName' => '*_s',
				'checkedFieldName' => 'name_s',
				'expectedIsMatching' => true
			),
			array(
				'configuredFieldName' => '*_s',
				'checkedFieldName' => 'names',
				'expectedIsMatching' => false
			),
			array(
				'configuredFieldName' => '*_s',
				'checkedFieldName' => 'this_is_s',
				'expectedIsMatching' => true
			),
			array(
				'configuredFieldName' => '*_s',
				'checkedFieldName' => 'this_is_something_else',
				'expectedIsMatching' => false
			),
			array(
				'configuredFieldName' => 'product_attribute_*',
				'checkedFieldName' => 'this_is_something_else',
				'expectedIsMatching' => false
			),
			array(
				'configuredFieldName' => 'product_attribute_*',
				'checkedFieldName' => 'product_attribute_color',
				'expectedIsMatching' => true
			),

		);
	}

	/**
	 * @param $configuredFieldName
	 * @param $checkedFieldName
	 * @param $expectedIsMatching
	 * @dataProvider getIsNameMatchingDataProvider
	 * @test
	 */
	public function testGetIsNameMatching($configuredFieldName, $checkedFieldName, $expectedIsMatching) {
		$this->dynamicField->setName($configuredFieldName);
		$this->assertSame(  $expectedIsMatching,
							$this->dynamicField->getIsNameMatching($checkedFieldName),
							'Unexpected matching state for method "getIsNameMatching"');

	}
}