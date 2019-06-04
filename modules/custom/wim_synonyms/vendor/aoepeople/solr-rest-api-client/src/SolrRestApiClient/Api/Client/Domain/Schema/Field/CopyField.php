<?php

namespace SolrRestApiClient\Api\Client\Domain\Schema\Field;

/**
 * Class CopyField
 *
 * @author Timo Schmidt <timo.schmidt@gmx.net>
 * @package SolrRestApiClient\Api\Client\Domain\Schema
 */
class CopyField {

	/**
	 * @var string
	 */
	protected $sourceName = '';

	/**
	 * @var string
	 */
	protected $targetName = '';

	/**
	 * @return string
	 */
	public function getSourceName() {
		return $this->sourceName;
	}

	/**
	 * @param string $sourceName
	 */
	public function setSourceName($sourceName) {
		$this->sourceName = $sourceName;
	}

	/**
	 * @return string
	 */
	public function getTargetName() {
		return $this->targetName;
	}

	/**
	 * @param string $targetName
	 */
	public function setTargetName($targetName) {
		$this->targetName = $targetName;
	}
}