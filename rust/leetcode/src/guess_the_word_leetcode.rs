impl Solution {
    pub fn find_secret_word(words: Vec<String>, master: &Master) {
        let mut possible = words;

        for _ in 0..30 {
            if possible.is_empty() {
                break;
            }

            let current = Self::pick_word(&possible);
            let result = master.guess(current.clone());

            if result == 6 {
                return;
            }

            possible.retain(|word| Self::count_matches(&current, word) == result);
        }
    }

    fn count_matches(w1: &str, w2: &str) -> i32 {
        let b1 = w1.as_bytes();
        let b2 = w2.as_bytes();
        let mut matches = 0;

        for i in 0..6 {
            if b1[i] == b2[i] {
                matches += 1;
            }
        }

        matches
    }

    fn pick_word(words: &[String]) -> String {
        if words.len() == 1 {
            return words[0].clone();
        }

        if words.len() <= 2 {
            return words[0].clone();
        }

        let mut best = words[0].clone();
        let mut best_score = usize::MAX;

        for candidate in words {
            let mut buckets = [0; 7];
            
            for other in words {
                if candidate != other {
                    let matches = Self::count_matches(candidate, other) as usize;
                    buckets[matches] += 1;
                }
            }

            let score: usize = buckets.iter().map(|&x| x * x).sum();

            if score < best_score {
                best_score = score;
                best = candidate.clone();
            }
        }

        best
    }
}