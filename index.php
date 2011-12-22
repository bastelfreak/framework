<?php
// something by bastelfreak, who knows...

// Erzwingen das Session-Cookies benutzt werden und die SID nicht per URL transportiert wird
ini_set( 'session.use_only_cookies', '1' );
ini_set( 'session.use_trans_sid', '0' );

// Session starten
session_start();

$debug = true;

/* Start - Errorhandling */
  if($debug === true){
    ini_set("display_errors", "on");
  }
  else{
    ini_set("display_errors", "off");
  }
  //set_error_handler("errorHandler");
  error_reporting(E_ALL);
  ini_set('error_reporting', E_ALL);
/* End - Errorhandling */

$rootPath = dirname(__FILE__);

require($rootPath."/int_res/config.inc");
require($rootPath."/int_res/basement.inc");
require($rootPath."/int_res/usermanagement.inc");
require($rootPath."/int_res/templateEngine.inc");
require($rootPath."/int_res/rss.inc");
$Configuration = new Config;
$Praefix = $Configuration->Site_Praefix;
$Suffix = $Configuration->Site_Suffix;
$Basement = new basement;

/* Start - Define a pseudofunction for errorhandling, php is unable to do this with a method */
function newErrorhandler($errorCode, $errorMessage, $file, $line){
	global $Basement;
	$Basement->errorHandler($errorCode, $errorMessage, $file, $line);
}
/* End */

set_error_handler("newErrorhandler");

if(!isset($_GET['site'])){	
	Header("Location: ?site=welcome");
}
elseif(file_exists($Praefix.$_GET["site"].$Suffix)){
	//require($Praefix."head".$Suffix);
  require($Praefix.$_GET['site'].$Suffix);
  //require($Praefix."footer".$Suffix);
	//echo $Head;
	if(isset($Output) && !empty($Output)){
		echo $Output;
	}
}	
else{
	echo "Something is wrong, please contact the admin at webmaster@framework.bastelfreak.de";
}
	


?>