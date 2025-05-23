# Duplicate Code Detection Tool
A simple Python3 tool (also available as a [GitHub Action](#github-action)) to detect
similarities between files within a repository.

## What?
A command line tool that receives a directory or a list of files and determines
the degree of similarity between them.

## Why?
The tool intends guide the refactoring efforts of a developer who wishes
to reduce code duplication within a component and improve its software
architecture.

Its development was initiated within the context of the
[DAT265 - Software Evolution Project](https://pingpong.chalmers.se/public/courseId/9754/lang-en/publicPage.do).

## How?
The tool uses the [gensim](https://radimrehurek.com/gensim/) Python library to
determine the similarity between source code files, supplied by the user.
The default supported languages are C, C++, JAVA, Python and C#.

### Dependencies
The following Python packages have to be installed:
  * nltk
    * `pip3 install --user nltk`
  * gensim
    * `pip3 install --user gensim`
  * astor
    * `pip3 install --user astor`
  * punkt
    * `python3 -m nltk.downloader punkt`

## Get started
Suppress the warnings (generated by the used libraries)
as `python3 -W ignore duplicate_code_detection.py` and then supply the necessary
arguments. More details can be found by running the tool with the `--help` option.

**Notice:** Due to the way the models are created, the more source files you
provide the tool the more accurate the similarity calculations are. In other
words, the bigger the project, the more useful the tool is.

### Example
If `duplicate-code-detection-tool` is the name where the tool resides in and
`smartcar_shield/src` contains the repository you want to check for source code
similarities between the files, then you can run the following to get the
similarity report:

`python3 -W ignore duplicate-code-detection-tool/duplicate_code_detection.py -d smartcar_shield/src/`

The result should look something like this:

![code duplication tool screenshot](https://i.imgur.com/wi1TnVM.png)

## GitHub Action

The tool is also available as a [GitHub Action](https://docs.github.com/en/actions) for easy integration
with projects hosted on GitHub. An example output of the tool can be seen
[here](https://github.com/platisd/smartcar_shield/pull/36#issuecomment-778635111).

The Action is meant to be triggered during **pull requests** to give the developers an impression
over the **degree of similarity** between the files in the source code. Below you will find a sample
workflow files that illustrate the usage.

Depending on the *size* of your project, you may want to have the tool running multiple times
(i.e in diffferent steps) that test specific parts of your repository for duplicate code.
This way you will not compare each file in your codebase with everything else and get back more
meaningful reports.

### Bare minimum

In the following example the tool will examine source code (the languages supported by default)
in the `src/` and `test/ut` directories *relative* to the root directory of your repository.
The results will be posted as a comment in the **pull request** that was opened.

```yaml
name: Duplicate code

on: pull_request

jobs:
  duplicate-code-check:
    name: Check for duplicate code
    runs-on: ubuntu-20.04
    steps:
      - name: Check for duplicate code
        uses: platisd/duplicate-code-detection-tool@master
        with:
          github_token: ${{ secrets.GITHUB_TOKEN }}
          directories: "src/, test/ut"
```

### Trigger on pull request comment

If you want to avoid the "spam" you should configure the tool to not always run. Specifically, if you
wish to trigger the Action manually, you can do so by leaving a comment in the pull request.

The following action will trigger the tool to be run when a comment containig `run_duplicate_code_detection_tool`
is posted in a pull request. The tool will run using the code in the pull request.

```yaml
name: Duplicate code

on: issue_comment

jobs:
  duplicate-code-check:
    name: Check for duplicate code
    # Trigger the tool only when a comment containing the keyword is published in a pull request
    if: github.event.issue.pull_request && contains(github.event.comment.body, 'run_duplicate_code_detection_tool')
    runs-on: ubuntu-20.04
    steps:
      - name: Check for duplicate code
        uses: platisd/duplicate-code-detection-tool@master
        with:
          github_token: ${{ secrets.GITHUB_TOKEN }}
          directories: "."
```

**Important:** Please note that due to the way GitHub Actions work, you will *first* have to merge this into your main
branch so it starts taking effect.

### Optional configuration

It may not make sense to compare all files or get a files with very low similarity reported.
In the following workflow, the different *optional* arguments are demonstrated.

For the various default values, please consult [action.yml](action.yml).

```yaml
name: Duplicate code

on: pull_request

jobs:
  duplicate-code-check:
    name: Check for duplicate code
    runs-on: ubuntu-20.04
    steps:
      - name: Check for duplicate code
        uses: platisd/duplicate-code-detection-tool@master
        with:
          github_token: ${{ secrets.GITHUB_TOKEN }}
          directories: "src"
          # Ignore the specified directories
          ignore_directories: "src/external_libraries"
          # Only examine .h and .cpp files
          file_extensions: "h, cpp"
          # Only report similarities above 5%
          ignore_below: 5
          # If a file is more than 70% similar to another, then the job fails
          fail_above: 70
          # If a file is more than 15% similar to another, show a warning symbol in the report
          warn_above: 15
          # Remove `src/` from the file paths when reporting similarities
          project_root_dir: "src"
          # Remove docstrings from code before analysis
          # For python source code only. This is checked on a per-file basis
          only_code: true
          # Leave only one comment with the report and update it for consecutive runs
          one_comment: true
          # The message to be displayed at the start of the report
          header_message_start: "The following files have a similarity above the threshold:"
```
## Using duplicate-code-check with pre-commit
To use Duplicate Code Detection Tool as a pre-commit hook with [pre-commit](https://pre-commit.com/) add the following to your `.pre-commit-config.yaml` file:
```yaml
-   repo: https://github.com/platisd/duplicate-code-detection-tool.git
    rev: ''  # Use the sha / tag you want to point at
    hooks:
    -   id: duplicate-code-detection
```
> **_NOTE:_** that this repository sets args: `-f`, if you are configuring duplicate-code-detection-tool using args you'll want to include either `-f` (`--files`) or `-d` (`--directories`).

## Limitations

- `only_code` option only works with python files for now
