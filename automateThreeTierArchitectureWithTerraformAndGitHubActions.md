# Overview
This is to record the procedure when I built this project. It is not intended to provide all information.

# Source Code
The source codes are located [here](https://github.com/alunwang/automate-three-tier-architecture-with-terraform-and-GitHub-actions) at GitHub.  
The source codes are mainly Terraform HCL codes which are used to define the resources for the three-tier-architecture application.

# Building procedure
## Create a new repository in GitHub
Repository name: automate-three-tier-architecture-with-terraform-and-GitHub-actions 
Select "Terraform" as .gitignore template 
Select "Add a README file"

## Create environment variables for the keys for both AWS and Terraform Cloud
Click "Settings" tab, and then select "Secrets->Actions->New repository secret", there create the following three environment variables:
```
AWS_ACCESS_KEY_ID
AWS_SECRET_ACCESS_KEY
TF_API_TOKEN
```
When deploying, these keys are used by system to access AWS and Terraform Cloud.

## Create a workflow
After the repository is created, click "Actions" tab, then locate the "Terraform" and selct "Configure", a yaml file named .github/workflows/terraform.yml is opened. 
Edit the file and remove all the instruction comments at the front of the file, insert the following code:
```
    env:
      AWS_ACCESS_KEY_ID: ${{ secrets.AWS_ACCESS_KEY_ID }}
      AWS_SECRET_ACCESS_KEY: ${{ secrets.AWS_SECRET_ACCESS_KEY }}
```
Finally commit this file.

## On a linux terminal, get the source codes by cloning the repository
Use the following command to clone the code (You need to create a ssh key and upload the public key file to your GitHub account before this operation):
```
$ git clone git@github.com:alunwang/automate-three-tier-architecture-with-terraform-and-GitHub-actions.git
$ cd automate-three-tier-architecture-with-terraform-and-GitHub-actions
```
## Create a new branch for your developing
Create a new branch named "feature" by using:
```
$ git branch
* main
$ git checkout -b feature
$ git branch
* feature
  main
```
And now you can do you development on the "feature" branch.

## Push the new "feature" branch to remote
When you are still on the "feature" branch, you can push this new branch to remote by using:
```
$ git push origin feature
```
If there is any change in the "feature" branch, that push will remind you to create "Pull request" to the "main" branch.

## Create a "Pull request", and then merge the request to the "main" branch
Go to the automate-three-tier-architecture-with-terraform-and-GitHub-actions repository in GitHub.

# Issue & Solution
## Error #1: No valid credentials
Issue error message:
```
Error: error configuring Terraform AWS Provider: no valid credential sources for Terraform AWS Provider found.
```
Solution:

First create environment variables for the repository in GitHub.  
Then add the code the workflow yaml file.

## Error #2: terraform fmt -check failure
Issue error message:
```
Run terraform fmt -check
/home/runner/work/_temp/8fb1e7c7-b30f-4ee9-bf91-e00e2332c16f/terraform-bin fmt -check
aws.tf

Error: Terraform exited with code 3.
```
Solution:
Even though running "terraform fmt -check" on Linux terminal, it seems to be successful without any error information, however, if we check the return code with the following command, we can see that it returns with non-zero code 3:
```
$ echo $?
3
```
But with the workflow, this non-zero code will lead to failure.  
The prolem with my case is caused by using editor in Windows which introduces "^M" in the code.  
1st solution is to remove all "^M" from the source codes.  
2nd solution is to the "-check" parameter from the "terraform fmt".
