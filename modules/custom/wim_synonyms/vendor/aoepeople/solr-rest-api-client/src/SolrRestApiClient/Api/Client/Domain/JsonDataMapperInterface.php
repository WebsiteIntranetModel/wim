<?php

namespace SolrRestApiClient\Api\Client\Domain;

interface JsonDataMapperInterface {

	/**
	 * @param $json
	 * @return object
	 */
	public function fromJson($json);

	/**
	 * @param $object
	 * @return string
	 */
	public function toJson($object);
}