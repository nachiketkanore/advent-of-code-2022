#![allow(unused)]
use std::collections::HashSet;
fn main() {}

// side adjacent
const DX: &[i32] = &[0, 0, 1, -1];
const DY: &[i32] = &[1, -1, 0, 0];

// diagonally adjacent
const DGX: &[i32] = &[1, 1, -1, -1];
const DGY: &[i32] = &[-1, 1, -1, 1];

enum Direction {
    Right,
    Left,
    Down,
    Up,
}

fn get_move(direction: Direction) -> (i32, i32) {
    match direction {
        Direction::Right => (0, 1),
        Direction::Left => (0, -1),
        Direction::Down => (1, 0),
        Direction::Up => (-1, 0),
    }
}

fn get_direction(ch: char) -> Direction {
    match ch {
        'R' => Direction::Right,
        'L' => Direction::Left,
        'D' => Direction::Down,
        'U' => Direction::Up,
        _ => panic!(),
    }
}

fn perform((mut hi, mut hj): (i32, i32), (mut ti, mut tj): (i32, i32)) -> (i32, i32) {
    if ti == hi && tj == hj {
        return (ti, tj);
    }
    let mut ok = (0..4).any(|id| {
        (ti + DX[id] == hi && tj + DY[id] == hj) | (ti + DGX[id] == hi && tj + DGY[id] == hj)
    });
    if ok {
        return (ti, tj);
    }
    // same row
    if ti == hi {
        if tj < hj {
            tj += 1;
        } else if tj > hj {
            tj -= 1;
        }
        return (ti, tj);
    }
    // same column
    else if tj == hj {
        if ti < hi {
            ti += 1;
        } else if ti > hi {
            ti -= 1;
        }
        return (ti, tj);
    }
    // diagonal
    for id in 0..4 {
        if ti + DGX[id] == hi && tj + DGY[id] == hj {
            // TODO ?
            return (ti, tj);
        }
    }
    // which quadrant
    if hi < ti && hj < tj {
        ti -= 1;
        tj -= 1;
    } else if hi < ti && hj > tj {
        ti -= 1;
        tj += 1;
    } else if hi > ti && hj > tj {
        ti += 1;
        tj += 1;
    } else if hi > ti && hj < tj {
        ti += 1;
        tj -= 1;
    }
    (ti, tj)
}

fn solve(input: &str, snake_len: usize) -> usize {
    let input: Vec<(Direction, i32)> = input
        .lines()
        .map(|line| {
            let tokens = line.split(' ').collect::<Vec<&str>>();
            let dir = tokens[0].chars().next().unwrap();
            (get_direction(dir), tokens[1].parse().unwrap())
        })
        .collect();

    let mut tail = vec![(1000, 1000); snake_len];
    let mut visited = HashSet::new();
    visited.insert(tail[0]);

    for (dir, iterations) in input {
        let (dx, dy) = get_move(dir);
        for _ in 0..iterations {
            let len = tail.len();
            tail[len - 1].0 += dx;
            tail[len - 1].1 += dy;
            for i in (0..len - 1).rev() {
                tail[i] = perform(tail[i + 1], tail[i]);
            }
            visited.insert(tail[0]);
        }
    }

    return visited.len();
}

fn solve_part1(input: &str) -> usize {
    solve(input, 2)
}

fn solve_part2(input: &str) -> usize {
    solve(input, 10)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn samples_part1() {
        let input = include_str!("../data/sample.txt");
        assert_eq!(solve_part1(input), 13);
    }

    #[test]
    fn samples_part2() {
        let input = include_str!("../data/sample-2.txt");
        assert_eq!(solve_part2(input), 36);
    }

    #[test]
    fn part1() {
        let input = include_str!("../data/input.txt");
        assert_eq!(solve_part1(input), 5695);
    }

    #[test]
    fn part2() {
        let input = include_str!("../data/input.txt");
        assert_eq!(solve_part2(input), 2434);
    }
}
