<?php

namespace SolrRestApiClient\Api\Client\Domain\StopWord;

/**
 * Class StopWord
 *
 * @author Timo Schmidt <timo.schmidt@aoe.com>
 * @package SolrRestApiClient\Api\Client\Domain\StopWord
 */
class StopWord {

	/**
	 * @var string
	 */
	protected $tag = '';

	/**
	 * @param string $tag
	 */
	public function setTag($tag) {
		$this->tag = $tag;
	}

	/**
	 * @return string
	 */
	public function getTag() {
		return $this->tag;
	}

	/**
	 * @var string
	 */
	protected $word = '';

	/**
	 * @return string
	 */
	public function getWord() {
		return $this->word;
	}

	/**
	 * @param string $word
	 */
	public function setWord($word) {
		$this->word = $word;
	}
}