<?php
/**
 * UploadFile.php
 */
require_once "wx_config.php";

class Wx_UploadVoice {
    private $myfile;

    public function Wx_UploadFile($file_key) {
        $this->myfile = $_FILES($file_key);
    }

    public function FileInfo() {
        try {
            $file_info = array();
            $file_info['name'] = $this->myfile['name']; // filename
            $file_info['ext'] = substr($this->myfile['name'], strrpos($this->myfile['name'], ".") + 1); // filename extension
            $file_info['type'] = $this->myfile['type'];
            $file_info['size'] = $this->myfile['size'];
            $file_info['tmp_name'] = $this->myfile['tmp_name']; // temp file path
            return $file_info;
        } catch (Exception $e) {
            return null;
        }
    }

    public function Upload($upload_path) {
        try {
            if (is_uploaded_file($this->myfile['tmp_name'])) {
                move_uploaded_file($this->myfile['tmp_name'], $upload_path);
                switch($this->myfile['error']) {
                    case 1:
                        $error = Wx_config::FileServerLimit;
                        break;
                    case 2:
                        $error = Wx_Config::FileWebLimit;
                        break;
                    case 3:
                        $error = Wx_Config::FileUploadPart;
                        break;
                    case 4:
                        $error = Wx_Config::FileLost;
                        break;
                    case 5:
                        $error = Wx_Config::FileTempLost;
                        break;
                    case 6:
                        $error = Wx_Config::FileCopyError;
                        break;
                    default:
                        $error = Wx_config::FileUploadOk;
                }
                return $error;
            } else {
                return Wx_Config::FileError;
            }
        } catch (Exception $e) {
            return Wx_Config::FileError;
        }
    }
}

?>