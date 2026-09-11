impl Solution {
    pub fn total_numbers(digits: Vec<i32>) -> i32 {
        let mut aa = [false; 1000];
        let bb = digits.len();
        (0..bb)
            .filter(|&cc| digits[cc] % 2 == 0)
            .for_each(|cc| {
                (0..bb).filter(|&dd| dd != cc).for_each(|dd| {
                    (0..bb)
                        .filter(|&ee| digits[ee] != 0 && ee != cc && ee != dd)
                        .for_each(|ee| {
                            aa[(digits[ee] * 100 + digits[dd] * 10 + digits[cc]) as usize] = true;
                        });
                });
            });
        aa.iter().filter(|&&asd| asd).count() as i32
    }
}
