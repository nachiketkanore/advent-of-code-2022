#![allow(unused)]
fn main() {}

fn solve_part1(input: &str) -> Vec<usize> {
    const LEN: usize = 4;
    let mut answers = Vec::new();
    for line in input
        .lines()
        .map(|line| line.chars().collect::<Vec<char>>())
    {
        let n = line.len();
        let mut found = false;
        for i in LEN - 1..n {
            let mut good = true;
            let mut mask = 0;
            for j in 0..LEN {
                let id = (line[i - j] as u8 - 'a' as u8);
                good &= (mask >> id & 1) == 0;
                mask |= 1 << id;
            }
            if good {
                found = true;
                answers.push(i + 1);
                break;
            }
        }
        assert!(found);
    }
    return answers;
}

fn solve_part2(input: &str) -> Vec<usize> {
    const LEN: usize = 14;
    let mut answers = Vec::new();
    for line in input
        .lines()
        .map(|line| line.chars().collect::<Vec<char>>())
    {
        let n = line.len();
        let mut found = false;
        for i in LEN - 1..n {
            let mut good = true;
            let mut mask = 0;
            for j in 0..LEN {
                let id = (line[i - j] as u8 - 'a' as u8);
                good &= (mask >> id & 1) == 0;
                mask |= 1 << id;
            }
            if good {
                found = true;
                answers.push(i + 1);
                break;
            }
        }
        assert!(found);
    }
    return answers;
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
