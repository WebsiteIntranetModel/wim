<?php

namespace SolrRestApiClient\Tests\Api\Client\Domain\Schema;

use SolrRestApiClient\Tests\BaseTestCase;
use SolrRestApiClient\Api\Client\Domain\Schema\SchemaDataMapper;

class SchemaDataMapperTestCase extends BaseTestCase {

	/**
	 * @var SchemaDataMapper
	 */
	protected $dataMapper = null;

	/**
	 * @return void
	 */
	public function setUp() {
		$this->dataMapper = new SchemaDataMapper();
	}

	/**
	 * @test
	 */
	public function canGetSchemaFromJson() {
		$fixtureContent = $this->getFixtureContent('Api/Client/Domain/Schema/Fixtures/schema1.json');
		$schema = $this->dataMapper->fromJson($fixtureContent);

		$this->assertEquals(12, $schema->getDynamicFields()->getCount(),'Restored unexpected amount of dynamic fields');
		$this->assertEquals(11, $schema->getDynamicFields()->getIsIndexedCount(),'Could not determine amount of dynamic indexed fields');
		$this->assertEquals(8, $schema->getDynamicFields()->getIsStoredCount(),'Could not determine amount of dynamic stored fields');
		$this->assertEquals(1, $schema->getDynamicFields()->getIsMultiValuedCount(),'Could not determine amount of dynamic multivalue fields');

	}
}