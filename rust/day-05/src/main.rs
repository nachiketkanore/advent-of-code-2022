#![allow(unused)]
fn main() {}

fn solve_part1(input: &str) -> String {
    let mut lines = input.split('\n').into_iter();
    let mut get_next_line = || -> String { lines.next().unwrap().to_string() };
    let n: usize = get_next_line().parse().unwrap();
    let mut stacks: Vec<String> = (0..n).map(|_| get_next_line()).collect();

    while let Some(line) = lines.next() {
        let vals: Vec<String> = line
            .split(' ')
            .filter(|val| val.len() > 0)
            .map(|line| line.to_string())
            .collect();
        if vals.is_empty() {
            break;
        }
        let (cnt, from, to) = (
            vals[1].parse::<usize>().unwrap(),
            vals[3].parse::<usize>().unwrap() - 1,
            vals[5].parse::<usize>().unwrap() - 1,
        );
        for _ in 0..cnt {
            assert!(stacks[from].len() > 0);
            let got = stacks[from].pop().unwrap();
            stacks[to].push(got);
        }
    }

    let mut answer = String::new();
    stacks.iter().for_each(|stack| {
        let top = stack.clone().pop().unwrap();
        answer.push(top);
    });
    return answer;
}

fn solve_part2(input: &str) -> String {
    let mut lines = input.split('\n').into_iter();
    let mut get_next_line = || -> String { lines.next().unwrap().to_string() };
    let n: usize = get_next_line().parse().unwrap();
    let mut stacks: Vec<String> = (0..n).map(|_| get_next_line()).collect();

    while let Some(line) = lines.next() {
        let vals: Vec<String> = line
            .split(' ')
            .filter(|val| val.len() > 0)
            .map(|line| line.to_string())
            .collect();
        if vals.is_empty() {
            break;
        }
        assert_eq!(vals.len(), 6);
        let (cnt, from, to) = (
            vals[1].parse::<usize>().unwrap(),
            vals[3].parse::<usize>().unwrap() - 1,
            vals[5].parse::<usize>().unwrap() - 1,
        );
        let mut got = String::new();
        for _ in 0..cnt {
            assert!(stacks[from].len() > 0);
            got.push(stacks[from].pop().unwrap());
        }
        got.chars()
            .into_iter()
            .rev()
            .for_each(|ch| stacks[to].push(ch));
    }

    let mut answer = String::new();
    stacks.iter().for_each(|stack| {
        let top = stack.clone().pop().unwrap();
        answer.push(top);
    });
    return answer;
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn samples_part1() {
        let input = include_str!("../data/sample.txt");
        assert_eq!(solve_part1(input), String::from("CMZ"));
    }

    #[test]
    fn samples_part2() {
        let input = include_str!("../data/sample.txt");
        assert_eq!(solve_part2(input), "MCD");
    }

    #[test]
    fn part1() {
        let input = include_str!("../data/input.txt");
        assert_eq!(solve_part1(input), "MQTPGLLDN");
    }

    #[test]
    fn part2() {
        let input = include_str!("../data/input.txt");
        assert_eq!(solve_part2(input), "LVZPSTTCZ");
    }
}
