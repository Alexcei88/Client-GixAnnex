function lengthStr(inputStr, maxLength) {
    var lengthf = inputStr.length;
//    console.log(lengthf);
//    console.log(maxLength);
    if(lengthf < maxLength)
        return lengthf;
    else
        return maxLength;
}
