export function solution(str: string): string {
    //разбиваем строку на массив символов с помощью метода split(),потом переворачиваем массив символов методом reverse()
    //и при помощи метода join() собираем обратно в строку
    return str.split("").reverse().join('');
}

console.log(solution("world"))