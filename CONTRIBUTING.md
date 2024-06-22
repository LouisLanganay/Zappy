# Contributing to Zappy

Thank you for considering contributing to Zappy! Your contributions help improve the project and make it better for everyone.

## Code of Conduct

This project adheres to a [Code of Conduct](CODE_OF_CONDUCT.md). By participating, you are expected to uphold this code. Please report unacceptable behavior to the maintainers via Discord.

## Getting Started

To start contributing to Zappy, follow these steps to set up your development environment:

### Prerequisites

Make sure you have the following dependencies installed:
- `raylib`

### Setup

1. Clone the repository:
   ```bash
   git clone https://github.com/LouisLanganay/zappy.git
   cd zappy
   ```
2. Build the binaries:
   ```bash
   make
   ```

   This will create the following binaries:
   - `zappy_gui`
   - `zappy_server`
   - `zappy_ai`

## How to Contribute

You can contribute to Zappy by submitting code changes. Here are the steps to follow:

1. **Fork the repository** to your own GitHub account.
2. **Clone the forked repository** to your local machine.
3. Create a **new branch** for your changes:
   ```bash
   git checkout -b feature-name
   ```
4. Make your changes following our **coding standards**. Commit messages should follow the **Karma** style.

## Issue and Pull Request Process

### Issues

If you encounter any issues or have feature requests, please use the [issue tracker](https://github.com/LouisLanganay/zappy/issues) and follow the provided template.

### Pull Requests

To submit a pull request (PR):

1. Ensure your code is well-tested.
2. Push your branch to GitHub.
3. Create a pull request from your branch to the `main` branch in the original repository.
4. Wait for a review. Make sure to respond to feedback and make any necessary changes.

## Development Workflow

We don't follow a specific branching strategy like Gitflow, but ensure your branches are meaningful and concise.

### Continuous Integration

Our CI/CD pipeline uses GitHub Actions to check the compilation of the code. Ensure your code passes these checks before submitting a PR.

## Testing

To run tests, use the provided Makefile:
```bash
make test
```

We do not have specific testing guidelines or frameworks, but ensure your tests are comprehensive and cover the new functionality.

## Documentation

Update the LaTeX documentation in the `Documentation` folder whenever you make changes that affect the project's functionality. Ensure the documentation is clear and concise.

## Communication

You can reach out to the maintainers via Discord for any questions or discussions. While we don't have regular meetings, we're active and will respond as soon as possible.

## Licensing

By contributing to Zappy, you agree that your contributions will be licensed under the MIT License.

Thank you for your contributions!
