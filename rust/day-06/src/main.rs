// #![allow(unused)]
fn main() {}

fn solve_part1(input: &str) -> Vec<usize> {
    const LEN: usize = 4;
    let mut answers = Vec::new();
    for line in input
        .lines()
        .map(|line| line.chars().collect::<Vec<char>>())
    {
        let n: usize = line.len();
        answers.push(
            (LEN - 1..n)
                .filter(|i| {
                    (0..LEN)
                        .fold(0usize, |mask, j| {
                            mask | (1 << (line[i - j] as u8 - 'a' as u8))
                        })
                        .count_ones() as usize
                        == LEN
                })
                .next()
                .unwrap()
                + 1,
        );
    }
    answers
}

fn solve_part2(input: &str) -> Vec<usize> {
    const LEN: usize = 14;
    let mut answers = Vec::new();
    for line in input
        .lines()
        .map(|line| line.chars().collect::<Vec<char>>())
    {
        let n: usize = line.len();
        answers.push(
            (LEN - 1..n)
                .filter(|i| {
                    (0..LEN)
                        .fold(0usize, |mask, j| {
                            mask | (1 << (line[i - j] as u8 - 'a' as u8))
                        })
                        .count_ones() as usize
                        == LEN
                })
                .next()
                .unwrap()
                + 1,
        );
    }
    answers
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn samples_part1() {
        let input = include_str!("../data/sample1.txt");
        assert_eq!(solve_part1(input), vec![7, 5, 6, 10, 11]);
    }

    #[test]
    fn samples_part2() {
        let input = include_str!("../data/sample2.txt");
        assert_eq!(solve_part2(input), vec![19, 23, 23, 29, 26]);
    }

    #[test]
    fn part1() {
        let input = include_str!("../data/input.txt");
        assert_eq!(solve_part1(input), vec![1953]);
    }

    #[test]
    fn part2() {
        let input = include_str!("../data/input.txt");
        assert_eq!(solve_part2(input), vec![2301]);
    }
}
