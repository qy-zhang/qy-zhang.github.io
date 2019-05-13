<?php
class Wx_Config {
    /**
     * return code
     */
    const FileUploadOk= "0";        //文件上传正常
    const FileServerLimit= "401";   //文件大小超出了服务器的空间大小
    const FileWebLimit= "402";      //要上传的文件大小超出浏览器限制
    const FileUploadPart= "403";    //文件仅部分被上传
    const FileLost= "404";          //没有找到要上传的文件
    const FileTempLost= "405";      //服务器临时文件夹丢失
    const FileCopyError= "406";     //文件写入到临时文件夹出错
    const FileError= "407";         //文件上传出错
}
?>