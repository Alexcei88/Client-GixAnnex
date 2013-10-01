
function lengthStr(inputStr, maxLength) {
    var lengthf = inputStr.length;
//    console.log(lengthf);
//    console.log(maxLength);
    if(lengthf < maxLength)
        return lengthf;
    else
        return maxLength;
}

// функция, которая обрезает начальный префикс file:// в LINUX системе
// на остальных опер системах позже
function GetFullStrPath(inputStr)
{
    var from = 7;
    var to = inputStr.length;
    var returnStr = inputStr.substring(from, to);
    return returnStr;
}

// получить относительный путь от полного пути относительно корневого пути репозитория
function GetRelativeStrPath(parentPathRepoStr, fullPathStr)
{
    // 1. находим строку parentPatRepoStr в подстроке fullPathStr
    if(parentPathRepoStr == fullPathStr)
        return "";

    var from = fullPathStr.indexOf(fullPathStr);
    var to   = fullPathStr.length;
    if(from == -1)
        // не нашли вхождения
        return fullPathStr;
    var relativeStr = fullPathStr.substring(from + parentPathRepoStr.length + 1, to);
    return relativeStr;
}

function GetOS(){
  var OperationSystem; // переменная для хранения названия ОСи
  if(navigator.userAgent.indexOf('UNIX')!=-1) OperationSystem = "UNIX";
  if(navigator.userAgent.indexOf('IRIX')!=-1) OperationSystem = "Irix";
  /*
   =Разные ОСи семейства Windows
  */
  if(navigator.userAgent.indexOf('Win')!=-1) OperationSystem = "Windows3.1 или NT";
  if((navigator.userAgent.indexOf('Win')!=-1) && (navigator.userAgent.indexOf('95')
   != -1)) OperationSystem = "Windows 95";
  if((navigator.userAgent.indexOf('Win')!=-1) && (navigator.userAgent.indexOf('98')
  != -1)) OperationSystem = "Windows 98";
  if((navigator.userAgent.indexOf('Win')!=-1) && (navigator.userAgent.indexOf('2000')
   != -1)) OperationSystem = "Windows 2000";
  if(navigator.userAgent.indexOf('Windows')!=-1) OperationSystem = "Windows XP";
  if(navigator.userAgent.indexOf("Windows NT 6.0")!=-1) OperationSystem = "Windows Vista";
  if(navigator.userAgent.indexOf("Windows NT 6.1")!=-1) OperationSystem = "Windows 7";
  if(navigator.userAgent.indexOf("Windows NT 6.2")!=-1) OperationSystem = "Windows 8";

  // Windows Phone, планшет, и Surface
  if(navigator.platform.toLowerCase().indexOf("win")!=-1
   && navigator.userAgent.toLowerCase().indexOf("touch")!=-1) OperationSystem = "Windows 8 multitouch";

  //---------------
  if(navigator.userAgent.indexOf('Linux')!=-1) OperationSystem = "Linux";
  if(navigator.userAgent.indexOf('Mac')!=-1) OperationSystem = "Mac OS";
  if(navigator.userAgent.indexOf('SunOS')!=-1) OperationSystem = "Sun Solaris";
  if(navigator.userAgent.indexOf('FreeBSD')!=-1) OperationSystem = "FreeBSD";

  return OperationSystem; // возвращаем значение переменной
 }
