
function lengthStr(inputStr, maxLength) {
    var lengthf = inputStr.length;
    if(lengthf < maxLength)
        return lengthf;
    else
        return maxLength;
}

// функция, которая обрезает начальный префикс file:// в LINUX системе
// на остальных опер системах позже
function getFullStrPath(inputStr)
{
    var from = 7;
    var to = inputStr.length;
    var returnStr = inputStr.substring(from, to);
    return returnStr;
}

// получить относительный путь от полного пути относительно корневого пути репозитория
function getRelativeStrPath(parentPathRepoStr, fullPathStr)
{
    // 1. находим строку parentPatRepoStr в подстроке fullPathStr
    if(parentPathRepoStr == fullPathStr)
        return "";

    var from = fullPathStr.indexOf(fullPathStr);
    var to   = fullPathStr.length;
    if(from == -1)
        // не нашли вхождения
        return fullPathStr;
    var relativeStr = fullPathStr.substring(from + parentPathRepoStr.length, to);
    return relativeStr;
}
