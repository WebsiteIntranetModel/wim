<?php

namespace SolrRestApiClient\Api\Client\Domain\Synonym;

/**
 * Class Synonym
 *
 * @author Timo Schmidt <timo.schmidt@aoe.com>
 * @package SolrRestApiClient\Api\Client\Domain\Synonym
 */
class Synonym {

	/**
	 * The main term
	 *
	 * @var string
	 */
	protected $mainWord = '';

	/**
	 * The related words with the same meaning
	 *
	 * @var array
	 */
	protected $wordsWithSameMeaning = array();

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
	 * @param string $word
	 */
	public function addWordsWithSameMeaning($word) {
		$this->wordsWithSameMeaning[$word] = $word;
	}

	/**
	 * @return array
	 */
	public function getWordsWithSameMeaning() {
		return $this->wordsWithSameMeaning;
	}

	/**
	 * @param array $wordsWithSameMeaning
	 */
	public function setWordsWithSameMeaning($wordsWithSameMeaning) {
		$this->wordsWithSameMeaning = $wordsWithSameMeaning;
	}

	/**
	 * @param string $mainWord
	 */
	public function setMainWord($mainWord) {
		$this->mainWord = $mainWord;
	}

	/**
	 * @return string
	 */
	public function getMainWord() {
		return $this->mainWord;
	}
}