impl Solution {
    pub fn next_greatest_letter(letters: Vec<char>, target: char) -> char {
        let _0 = letters.len();
        if target < letters[0] || target >= letters[_0 - 1] {
            return letters[0];
        }
        let mut _1: usize = 0;
        let mut _2: usize = _0;
        while _1 < _2 {
            let _3 = _1 + (_2 - _1) / 2;
            if letters[_3] > target {
                _2 = _3;
            } else {
                _1 = _3 + 1;
            }
        }
        letters[_1]
    }
}
