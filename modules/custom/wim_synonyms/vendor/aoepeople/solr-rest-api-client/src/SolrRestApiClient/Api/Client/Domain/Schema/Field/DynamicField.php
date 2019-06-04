<?php

namespace SolrRestApiClient\Api\Client\Domain\Schema\Field;

/**
 * Class DynamicField
 *
 * @author Timo Schmidt <timo.schmidt@gmx.net>
 * @package SolrRestApiClient\Api\Client\Domain\Schema
 */
class DynamicField extends AbstractField {

	/**
	 * This method is used to check if a certain fieldName matches to the dynamic fieldName.
	 *
	 * @param $concreteFieldName
	 * @return boolean
	 */
	public function getIsNameMatching($concreteFieldName) {
		$pattern = '/^'.str_replace('*','.*',$this->getName()).'$/';
		$matches = preg_match($pattern,$concreteFieldName);

		return $matches >= 1;
	}
}