<?php
class templateEngine extends basement{

	##
	# This fucking b&auml;m script parse every template file and puts content into it
	##
	## todo public function bockMod($blockname, tpl), erstellt einen block falls er noch nicht existiert, 
	## hauml;ngt tpl hinten dran wie addBlock+setBlockTemplate
	private $content = array(); 
	private $blocks = array();
	//private $blockTemplate = array();
	private $template = "";
	private $stylePresent = "generic";
	private $style = "";
	private $tplDir = "templates";
	private $ErrorMsg;
		
	function  __construct($user){
		$this->getStyle($user);
		$this->setTemplate("head.tpl");
	}
	
	public function addBlock($blockName = ""){
		if(!empty($blockName)){
			$this->blocks[$blockName] = "";
		}
	}
	
	public function setBlockTemplate($blockName = "", $tpl = ""){
		$path = $this->tplDir."/".$this->style."/".$tpl;
		if(!file_exists($path)){
			$this->ErrorMsg .= "<span>Error: Style ".$this->style." doesn't contain the ".$tpl." file. path is ".$path."</span><br>\n";
			$path = $this->tplDir."/".$this->stylePresent."/".$tpl;
			if(!file_exists($path)){
				echo "you failed sooo bad...";
				exit;			
			}
		}	
		$this->blocks[$blockName] .= file_get_contents($path);
	}
	
	public function setBlockContent($blockName, $var, $content){
		$this->blocks[$blockName] = str_replace("{".$var."}", $content, $this->blocks[$blockName]);
	}
	
	public function addBlock2Content($blockName){
		if(array_key_exists($blockName, $this->blocks) && !array_key_exists($blockName, $this->content)){
			$this->content[$blockName] = $this->blocks[$blockName];
		}
	}
	
	/**
	 * setContent
	 *
	 * Saves any content and related vars for templates
	 *
	 * @param string $var			the related var
	 * @param string $content	the importent content
	 * 
	 * @return TRUE/FALSE			depends on what happends
	 */
	public function setContent($var = "", $content = ""){
		if(empty($var)){
			$error = "var is empty";
			return FALSE;
		}
		elseif(empty($content)){
			$error = "content is empty";
			return FALSE;
		}
		elseif(!is_string($var)){
			$error = "var is not a string";
			return FALSE;
		}
		elseif(!is_string($content)){
			$error = "content is not a string";
			return FALSE;			
		}
		elseif(array_key_exists($var, $this->content)){
			$error = "key is twice, race condition :p";
			return FALSE;
		}
		else{
			$this->content[$var] = $content;
			return TRUE;
		}
	}
	

	
	/**
	* setTemplate
	*
	* loads templatefiles
	*
	* @param String $template template name
	*/
	public function setTemplate($template = ""){
		$path = $this->tplDir."/".$this->style."/".$template;
		if(!file_exists($path)){
			$this->ErrorMsg .= "<span>Error: Style ".$this->style." doesn't contain the ".$template." file. path is ".$path."</span><br>";
			$path = $this->tplDir."/".$this->stylePresent."/".$template;
			if(!file_exists($path)){
				echo "you failed sooo bad...";
				exit;			
			}
		}
		if(empty($this->template)){
			$this->template = file_get_contents($path);
		}
		else{
			$this->template .= file_get_contents($path);
		}
	}
	
	/**
	* parseTemplate
	*
	* replaces every var in the template with the equivalent content
	*/
	public function parseTemplate(){
		$this->setTemplate("footer.tpl");
		if(!array_key_exists("css", $this->content)){
			$this->setContent("css", " ");
		}
		if(!array_key_exists("js", $this->content)){
			$this->setContent("js", " ");
		}
		foreach($this->content as $key => $value){
			$this->template = str_replace("{".$key."}", $value, $this->template);
		}
		//$tidy = tidy_parse_string($this->template);
		//$this->template = $tidy->html();
	}
	
	/**
	* getTemplate
	* 
	* @return String template		returns the template
	*/ 
	public function getTemplate(){
		return $this->template;
	}
	
	/**
	* showTemplate
	*
	* echo the template
	*/
	public function showTemplate(){
		echo $this->template;
	}
	
	private function getStyle($user){
		$array = $user->getUserInfo();
		if($array === ARRAY()){
			if(array_key_exists("style", $array)){
				if(is_dir("templates/".$array["style"])){
					$this->style = $array["style"];
				}
			}
			else{
				$this->style = $this->stylePresent;
			}
		}
		//$this->template .= "<pre>".print_r($array, true)."</pre>";
	}
}