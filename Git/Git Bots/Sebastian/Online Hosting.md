# Discord-Git Bot

## Connecting The Bot to AWS EC2

To set up and host your Discord bot on AWS, you'll need to use Amazon's **EC2 (Elastic Compute Cloud)** service, which provides scalable virtual servers. Below is a step-by-step guide to get your Discord bot running on an EC2 instance.

### 1. Create an AWS Account
   - Go to the [AWS website](https://aws.amazon.com/), and create a new account.
   - You will need to provide billing information, though AWS offers a **free tier** that provides 12 months of limited free usage.

---

### 2. Launch an EC2 Instance
   - After signing in to the AWS Management Console, search for **EC2** and click on **Launch Instance**.
   - Choose the **Amazon Machine Image (AMI)**:
     - Select **Ubuntu Server 22.04 LTS** (or the latest stable version).
   - Choose an **Instance Type**:
     - For the free tier, select **t2.micro**.
   - **Configure Instance Details**:
     - Default settings are fine for most cases.
   - **Add Storage**:
     - 8GB of storage is enough for most small projects.
   - **Add Tags** (optional):
     - You can skip this step.
   - **Configure Security Group**:
     - Add rules for **SSH** (port 22) and **HTTP** (port 80).
   - **Key Pair

To find the public IP address of your EC2 instance, follow these steps:

> [!tip]- Finding the Public IP of Your EC2 Instance
> 
> 1. **Log in to AWS Management Console**:
>    - Go to the [AWS Management Console](https://aws.amazon.com/console/).
>    - Sign in with your AWS account.
> 
> 2. **Navigate to EC2 Dashboard**:
>    - In the AWS Management Console, type **EC2** in the search bar and select **EC2** from the results.
> 
> 3. **Instances Section**:
>    - In the left sidebar, click on **Instances** under the **Instances** section.
> 
> 4. **Select Your Instance**:
>    - You will see a list of your EC2 instances. Locate the instance for your Discord bot.
>    - Click on the instance ID or select the checkbox next to it to view the instance details.
> 
> 5. **View Public IP Address**:
>    - In the **Description** tab at the bottom, you’ll find various details about your instance.
>    - Look for the field labeled **IPv4 Public IP**. This is your EC2 instance's public IP address.
> 
> ### Example Screenshot Reference
> > [!image]- In the instance details, it should look something like this:
> >![[Pasted image 20240926150520.png]]
> >
> >```
> >IPv4 Public IP: 203.0.113.25
> >```
> 
> You can use this public IP address to connect to your EC2 instance via SSH or to interact with your Discord bot running on that instance.
> 
> ### Additional Note
> If your instance doesn’t have a public IP, you may need to adjust your instance's settings to assign an Elastic IP or ensure it is launched in a public subnet within a VPC that allows public access.
> 

### 1. Launch the EC2 Instance (Already Done)

You already created the instance, so we’ll jump straight to connecting to it and setting up the bot.

### 2. Find Your `.pem` File
   - When you created your EC2 instance, you should have downloaded a `.pem` file (your private key).
   - Ensure that this `.pem` file is located in a directory you can easily navigate to using Git Bash.

### 3. Connect to the EC2 Instance Using Git Bash
   - Open **Git Bash** on Windows.
   - Navigate to the directory where your `.pem` file is stored:
     ```bash
     cd /path/to/your-pem-file
     ```
   - Use the following command to connect to your EC2 instance:
     ```bash
     ssh -i "your-key.pem" ubuntu@your-public-ip
     ```
   - Replace `"your-key.pem"` with the name of your private key file and `your-public-ip` with the **Public IP address** of your EC2 instance (you can find this in the **EC2 Dashboard** under **Instances**).

### 4. Set Up Node.js and Git on the EC2 Instance
Once you’re connected to the EC2 instance, you’ll need to install **Node.js** and **Git**:

   - **Update the instance**:
     ```bash
     sudo apt update
     ```

   - **Install Node.js and npm**:
     ```bash
     sudo apt install nodejs npm
     ```

   - **Install Git** (if not already installed):
     ```bash
     sudo apt install git
     ```

   - Verify that **Node.js** and **npm** are installed:
     ```bash
     node -v
     npm -v
     ```

### 5. Clone Your Discord Bot Repository
   - Use Git to clone your bot's code from GitHub:
     ```bash
     git clone https://github.com/yourusername/your-bot-repository.git
     cd your-bot-repository
     ```

### 6. Set Up Your Environment Variables
   - Create a `.env` file to store your **Discord Bot Token**, **GitHub Token**, and other environment variables.
     ```bash
     nano .env
     ```
   - Add your environment variables:
     ```
     DISCORD_BOT_TOKEN=your-discord-bot-token
     GITHUB_TOKEN=your-github-token
     ```
   - Save and exit the file.

### 7. Install Project Dependencies
   - Install the required packages for your Discord bot by running:
     ```bash
     npm install
     ```

### 8. Run the Bot
   - You can start your bot using:
     ```bash
     node index.js
     ```

   - At this point, your bot should connect to Discord. You should see output indicating a successful connection.

### 9. Keep the Bot Running with PM2
Since you don't want the bot to stop running when you close your Git Bash session, install and use **PM2** (a process manager):

   - **Install PM2 globally**:
     ```bash
     sudo npm install -g pm2
     ```

   - **Start your bot with PM2**:
     ```bash
     pm2 start index.js --name "discord-bot"
     ```

   - Ensure that **PM2** restarts on reboot:
     ```bash
     pm2 startup
     pm2 save
     ```

### 10. Optional: Use Elastic IP for a Static IP Address
   - If you want to ensure your bot's IP address remains the same after a reboot, you can assign an **Elastic IP** to your EC2 instance from the EC2 Dashboard.

### 11. Optional: Automate with GitHub (Optional)
   - Set up a Continuous Integration/Continuous Deployment (CI/CD) pipeline with **GitHub Actions** to automatically push updates to your bot when you push code changes to your GitHub repository.

---

