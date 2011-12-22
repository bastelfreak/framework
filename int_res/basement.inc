<?php
require "ext_res/cerberus-filterclass/input-filter.php";

class basement extends Config{
	
	private $db;
	private $cleaner;// = new Input_Cleaner(); 
	
	/*function  __construct(){
		$this->cleaner = new Input_Cleaner(); 
	}*/
	public function db_connect(){
		$this->db = new MySQLi(parent::get_dbhost(), parent::get_dbuser(), parent::get_MySQL_Passwort(), parent::get_dbname());
		if (mysqli_connect_errno() == 0){
			$this->db->Query("SET 
							character_set_results = 'utf-8', 
							character_set_client = 'utf-8', 
							character_set_connection = 'utf-8', 
							character_set_database = 'utf-8', 
							character_set_server = 'utf-8'
						"); 
			$a = $this->db;
			//return $this->db;
			return $a;
		}
		else{
			return false;
		}
	}
	
	public function getMySQL(){
		return $this->db;
	}
	
	
	protected function CleanGet($clean = ""){
		if(!empty($clean)){
			$clean = trim(strip_tags($clean));
			return $clean;
		}
	}
	
	public function errorHandler($errorCode, $errorMessage, $file, $line){
			switch ($errorCode){
				case E_ERROR:
					$type = 'E_ERROR';
					break;
				case E_WARNING:
					$type = 'E_WARNING';
					break;
				case E_NOTICE;
					$type = 'E_NOTICE';
					break;
				default:
					$type = 'UNKNOWN';
					break;
			}  
			$sql = "INSERT INTO log_error (	`type`,
																		`description`,
																		`file`,
																		`line`,
																		`date`
																	) 
																	VALUES (	'".$type."',
																						'".addslashes($errorMessage)."',
																						'".$file."',
																						'".$line."',
																						now()
																					)";
			$Sql = $this->db_connect();
			$Sql->Query($sql);
			return TRUE;
		}
}







?>