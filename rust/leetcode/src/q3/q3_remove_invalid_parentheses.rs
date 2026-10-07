impl Solution {
    pub fn remove_invalid_parentheses(s: String) -> Vec<String> {
        fn asd(
            aa: &mut [u8],
            bb: usize,
            cc: usize,
            dd: usize,
            ee: usize,
            ff: usize,
            gg: bool,
            hh: &mut Vec<String>,
        ) {
            if aa.len() - bb < dd + ee + ff {
                return;
            }
            if bb == aa.len() {
                let ii = std::str::from_utf8(&aa[..cc]).unwrap();
                // ponytail: linear dedup avoids extra heap; use HashSet if outputs grow.
                if !hh.iter().any(|jj| jj == ii) {
                    hh.push(ii.to_owned());
                }
                return;
            }
            let ii = aa[bb];
            if gg || bb == 0 || ii != aa[bb - 1] {
                match ii {
                    b'(' if dd > 0 => asd(aa, bb + 1, cc, dd - 1, ee, ff, true, hh),
                    b')' if ee > 0 => asd(aa, bb + 1, cc, dd, ee - 1, ff, true, hh),
                    _ => {}
                }
            }
            if ii == b')' && ff == 0 {
                return;
            }
            let jj = aa[cc];
            aa[cc] = ii;
            asd(
                aa,
                bb + 1,
                cc + 1,
                dd,
                ee,
                match ii {
                    b'(' => ff + 1,
                    b')' => ff - 1,
                    _ => ff,
                },
                false,
                hh,
            );
            aa[cc] = jj;
        }
        let (aa, bb) = s.bytes().fold((0usize, 0usize), |(aa, bb), cc| match cc {
            b'(' => (aa + 1, bb),
            b')' if aa > 0 => (aa - 1, bb),
            b')' => (aa, bb + 1),
            _ => (aa, bb),
        });
        if aa == 0 && bb == 0 {
            return vec![s];
        }
        let mut cc = s.into_bytes();
        let mut dd = Vec::new();
        asd(&mut cc, 0, 0, aa, bb, 0, false, &mut dd);
        dd
    }
}

#[cfg(test)]
mod aa {
    use super::Solution;
    #[test]
    fn aa() {
        for (aa, bb) in [
            ("()())()", vec!["(())()", "()()()"]),
            ("(a)())()", vec!["(a())()", "(a)()()"]),
            (")(", vec![""]),
            ("", vec![""]),
            ("abc", vec!["abc"]),
            ("((()))", vec!["((()))"]),
            ("(((", vec![""]),
            (")))", vec![""]),
            ("(()", vec!["()"]),
            ("())", vec!["()"]),
            ("é(🙂))", vec!["é(🙂)"]),
        ] {
            let mut cc = Solution::remove_invalid_parentheses(aa.into());
            cc.sort_unstable();
            assert_eq!(cc, bb, "{aa}");
        }
    }
}
