impl Solution {
    pub fn count_servers(grid: Vec<Vec<i32>>) -> i32 {
        grid.iter().fold(0, |aa, bb| match bb.iter().sum::<i32>() {
            0 => aa,
            1 => {
                let cc = bb.iter().position(|&dd| dd == 1).unwrap();
                aa + (grid.iter().filter(|ee| ee[cc] == 1).count() > 1) as i32
            }
            asd => aa + asd,
        })
    }
}
