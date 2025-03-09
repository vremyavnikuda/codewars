
/*
В этом простом задании вам дается число, и вы должны сделать его отрицательным. Но, может быть, число уже отрицательное?
Notes

Examples
makeNegative(1);  // return -1
makeNegative(-5); // return -5
makeNegative(0);  // return 0

The number can be negative already, in which case no change is required.
Zero (0) is not checked for any specific sign. Negative zeros make no mathematical sense.
*/
export const makeNegative = (num: number): number => {
    //проверяем отрицательное ли число (если число >0)
    if(num>0){
        //возвещаем его отрицательное представление 
        return -num
    }
    //и возвращаем результат
    return num;
};

//проверка результата
console.log(makeNegative(55));


