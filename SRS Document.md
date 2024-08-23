# 1. Introduction

<br>

## 1.1 Purpose

This Software Requirements Specification (SRS) document outlines the requirements for the Core Banking Solution. The CBS is designed to manage the essential banking functions for a private bank in Seychelles, including account management, branch operations, customer management, loan processing, and transaction handling. This document provides a detailed description of the system’s functionality and is intended to serve as a comprehensive guide for developers, testers, project managers, and stakeholders involved in the project.

<br>

## 1.2 Document Conventions

This document adheres to the following conventions:

- Heading styles are used for headings 
- **Bold** text is used for key terms.
- _Italic_ text is used for emphasis.
- Times New Roman font is used for general text.
- Monospaced font is used for code snippets and system paths.
- Priorities for requirements are indicated using the following format:
	- **High**: Essential for initial release.
	- **Medium**: Important but not critical.
	- **Low**: Nice to have, will not impact the system significantly if omitted.
- Each requirement statement is assigned its own priority, independent of higher-level requirements.

<br>

## 1.3 Intended Audience and Reading Suggestions

This SRS is intended for a diverse audience including:

- **Developers**: To understand the functional and non-functional requirements of the system.
- **Project Managers**: To get an overview of the project scope, timelines, and deliverables.
- **Marketing Staff**: To understand the key features and benefits of the system.
- **Testers**: To design and execute test cases based on the specified requirements.
- **Documentation Writers**: To develop user manuals and help guides.

Readers are advised to begin with section 1 for an introduction, followed by section 2 for a product description, and section 3 for Interface Requirements. Developers and testers should pay special attention to the System Features in section 4 and Other Nonfunctional Requirements in section 5

<br>

## 1.4 Product Scope

The purpose of this software development project is to create a Core Banking Solution (CBS) for a private bank in Seychelles. Key functionalities include:

- **Account Management**: Opening, closing, and maintaining customer accounts.
- **Branch Operations**: Managing branch information and operations.
- **Customer Management**: Handling customer information and interactions.
- **Loan Processing**: Managing loan applications, approvals, and repayments.
- **Transaction Handling**: Recording and processing financial transactions.

The CBS aligns with the bank’s strategic goal to enhance operational efficiency, improve customer service, and support future growth.

<br>

## 1.5 References

IEEE. _IEEE Std 830-1998 IEEE Recommended Practice for Software Requirements Specifications._ IEEE Computer Society, 1998.

<br>
<br>

# 2.0 Overall Description

<br>

## 2.1 System Environment

The **Bank Transaction and Loan Processing System** is an advanced banking platform designed to replace the outdated DOS-based system currently in use by Bank A, a private bank in Seychelles. The primary goal of this new system is to modernize the bank's operations, ensure compliance with Seychelles' financial regulations, and lay the groundwork for future expansion, including integration with the national banking switch for cross-bank transactions and ATM services.

<br>

## 2.1.1 Deployment Architecture

The system will be deployed across all branches of Bank A, with the head office acting as the central hub. A secure **leased line network** will connect each branch to the head office, facilitating real-time communication and data transfer. The system's architecture will include:

- **Central Servers**: Located at the head office, these servers will host the core banking software, manage databases, and handle transaction processing.
- **Branch Terminals**: Bank employees will access the system through secure terminals at each branch, allowing for branch-level operations such as account management and loan processing.
- **Customer Portal**: Customers will interact with the system via an online portal, enabling them to manage their accounts, transfer funds, and apply for loans from anywhere.
- **Data Security Measures**: The system will incorporate robust security features, including encryption, secure login protocols, and regular audits, to protect sensitive banking data.

<br>

## 2.1.2 System Interfaces

The system will interact with several external and internal interfaces, including:

- **Banking Regulatory Systems**: Ensures compliance with national financial regulations through regular data exchanges.
- **Future Integration with National Banking Switch**: Although not included in the initial phase, the system is designed to integrate seamlessly with the Seychelles national banking switch for cross-bank transactions and ATM operations.
- **Reporting Tools**: Provides secure access to reports generated by the system, available only to authorized personnel like branch managers.

<br>

## 2.2 Functional Requirements Specification

The Bank Transaction and Loan Processing System is divided into several key functional areas, each encompassing specific use cases. These functional areas include branch management, account management, internal fund transfers, loan processing, and reporting.

### 2.2.1 Branch Management Use Cases

- **Use case: Manage Branches**
	- **Description**: Allows the bank to manage branch-specific details, such as updating branch information, assigning branch managers, and maintaining employee records. This functionality is crucial for ensuring that each branch operates efficiently and complies with the bank's internal policies.
	- **Priority**: _High_
	- **Actors**: Branch Manager, System Administrator

### 2.2.2 Account Management Use Cases

- **Use case: Create and Manage Accounts**
	- **Description**: Supports the creation and ongoing management of customer accounts, including Savings Accounts, Checking Accounts, and Fixed Deposits. The system will enforce withdrawal limits for Savings Accounts and automatically calculate and apply interest rates based on the type of account.
	- **Priority**: _High_
	- **Actors**: Bank Employees, Customers

- **Use case: Link Fixed Deposit to Savings Account**
	- **Description**: Allows customers to start Fixed Deposits linked to their Savings Accounts. The system will calculate interest on the Fixed Deposits monthly and deposit it into the linked Savings Account.
	- **Priority**: _High_
	- **Actors**: Bank Employees, Customers

- **Use case: Update Account Information**
	- **Description**: Enables bank employees to update account information, such as personal details, account status, and account type.
	- **Priority**: _Medium_
	- **Actors**: Bank Employees

### 2.2.3 Internal Fund Transfers Use Case

- **Use case: Transfer Funds**
	- **Description**: Enables customers to transfer funds between their accounts within the bank. This feature supports real-time processing, allowing for instant fund availability. The system will also ensure that no transaction fees are applied to these internal transfers.
	- **Priority**: _High_
	- **Actors**: Customers, Bank Employees

### 2.2.4 Loan Processing Use Cases

- **Use case: Apply for Loan In-Branch**
	- **Description**: Allows customers to apply for loans directly at a branch with assistance from bank employees. Loan applications require branch manager approval before they can be processed further. This feature supports both personal and business loans, with customizable loan terms based on the customer’s profile.
	- **Priority**: _High_
	- **Actors**: Customers, Bank Employees, Branch Manager

- **Use case: Apply for Loan Online**
	- **Description**: Provides customers with the convenience of applying for loans online if they hold an existing Fixed Deposit with the bank. The system automates the approval process, leveraging predefined criteria, and does not require branch manager involvement for these cases.
	- **Priority**: _High_
	- **Actors**: Customers

- **Use case: Calculate and Track Loan Installments**
	- **Description**: Once a loan is approved, the system will automatically calculate the monthly installments, schedule payment dates, and track each installment as it is paid. The system will generate reminders for customers and alerts for bank employees in case of missed payments.
	- **Priority**: _High_
	- **Actors**: Customers, Bank Employees

### 2.2.5 Reporting Use Cases

- **Use case: Generate Branch-Wise Transaction Report**
	- **Description**: Branch managers can generate detailed reports of all transactions that occurred within their branch during a specified period. These reports are essential for internal audits and compliance with regulatory requirements.
	- **Priority**: _Medium_
	- **Actors**: Branch Manager, System Administrator

- **Use case: Generate Branch-Wise Loan Installment Report**
	- **Description**: This feature allows branch managers to generate reports on loan installments, focusing on payments that are late or missed. These reports help the branch manager take necessary actions to ensure loan recovery.
	- **Priority**: _Medium_
	- **Actors**: Branch Manager

<br>
<br>

# 3. External Interface Requirements

## 3.1 User Interfaces  
The online banking system will provide a web-based user interface that allows users to perform various banking functions. The interface will adhere to modern web design principles, ensuring it is intuitive, responsive, and accessible. Key characteristics include:

- **Login/Registration Screens:** Secure login and account registration screens with standard input fields (username, password) and security measures like CAPTCHA and two-factor authentication.
- **Dashboard:** A central dashboard displaying account balances, recent transactions, and quick links to common actions such as transfers and bill payments.
- **Account Management:** Interfaces for viewing account details, managing account settings, and downloading statements.
- **Transaction Management:** Screens for initiating transfers, paying bills, and viewing transaction histories.
- **Notifications:** A section for displaying alerts, messages, and important notifications from the bank.
- **Help and Support:** Access to customer support via chat, email, or phone, with a help section that includes FAQs and guides.
- **Standard Buttons and Functions:** Consistent use of standard buttons like "Submit," "Cancel," and "Help" across all screens. Keyboard shortcuts for common actions (e.g., "Ctrl+T" for new transfer) will be provided.
- **Error Messages:** Clear and concise error messages will be displayed when users encounter issues.

## 3.2 Hardware Interfaces  
The web app will primarily interact with client devices such as desktop computers, laptops, tablets, and smartphones. It will support modern web browsers on various operating systems (e.g., Windows, macOS, Android, iOS). Key hardware interface characteristics include:

- **Device Compatibility:** The application will be compatible with devices having different screen sizes and resolutions, ensuring responsive design and a consistent user experience.
- **Input Devices:** The app will support input via mouse, keyboard, touchscreens, and virtual keyboards.
- **Security Devices:** Integration with hardware security modules (HSMs) and secure elements for transactions requiring strong authentication (e.g., smart cards or biometric devices).

## 3.3 Software Interfaces  
The online banking system will interact with several software components, including:

- **Operating Systems:** Compatibility with popular operating systems like Windows, macOS, Android, and iOS.
- **Databases:** Integration with secure databases for storing user data, transaction records, and account details. The system will use APIs to communicate with the database, ensuring data consistency and integrity.
- **Payment Gateways:** Interfaces to connect with third-party payment gateways for processing payments and transfers.
- **External APIs:** Interaction with external services like credit bureaus, and SMS/email notification services.
- **Web Servers:** The system will run on secure web servers, utilizing HTTPS for encrypted communication.
- **Libraries and Frameworks:** The application will leverage modern web development frameworks (e.g. React) and libraries for enhanced functionality and user experience.

## 3.4 Communications Interfaces  
The online banking system will require various communication functions to operate efficiently. These include:

- **Web Protocols:** The app will use HTTP/HTTPS for communication between client devices and the server. All data exchanges will be encrypted using SSL/TLS to ensure security.
- **Email and SMS Notifications:** The system will send transactional alerts, OTPs (One-Time Passwords), and other notifications via email and SMS. These communications will follow standard formats like SMTP for emails and SMS gateways for text messages.
- **API Communication:** The app will communicate with external APIs over RESTful services, using JSON or XML for data interchange. The APIs will be secured using OAuth or other authentication mechanisms.
- **Data Synchronization:** Real-time data synchronization will be implemented between the client and server, ensuring that user actions (e.g., initiating a transfer) are reflected instantly across all devices.
- **Security Protocols:** The system will use strong encryption algorithms for data at rest and in transit, and will adhere to industry standards like PCI DSS for handling payment information.

<br>
<br>

# 4. System Features

<br>

## 4.1    Customer management

### 4.1.1 Description and Priority

**Description**: The Customer Management feature allows the bank to manage customer data, including the creation, updating, and deletion of customer profiles. It supports the classification of customers as either individuals or organizations (e.g., NGOs, companies), and handles the association of customers with multiple accounts across different branches.

**Priority**: *High*

**Benefit**: 9 - Ensures that accurate customer data is maintained, which is critical for all banking operations.

**Penalty**: 8 - Inconsistent or incorrect customer data can lead to errors in transactions, account management, and loan processing.

**Cost:** 6 - Involves designing a robust database structure and secure access controls.

**Risk**: 7 - Data integrity and security are paramount, as customer data is sensitive and must comply with regulations.

<br>

## 4.1.2 Stimulus/Response Sequences

**Stimulus**: A customer visits a branch to open a new account.
- **Response**: The system prompts the bank employee to create a new customer profile by entering personal or organizational details, such as name, address, and identification information. Once the profile is created, the customer can proceed to open an account.

**Stimulus**: A customer requests to update their personal details, such as address or phone number.
- **Response**: The system allows the bank employee to search for the customer profile and update the necessary information. The system saves the changes and logs the update.

**Stimulus**: A bank employee needs to retrieve a customer’s profile for verification during a transaction.
- **Response**: The system searches the database based on customer ID or other identifiers, retrieves the profile, and displays it for the employee’s review.

**Stimulus**: A customer requests to close their account and delete their profile.
- **Response**: The system verifies that the customer has no pending transactions or obligations (e.g., loans), and then proceeds to deactivate the profile and associated accounts.

<br>

## 4.1.3 Functional Requirements

**REQ-1**: The system shall allow employees to create new customer profiles, including fields for personal information (name, address, date of birth, identification number) or organizational information (organization name, registration number, contact details).

**REQ-2**: The system shall allow customers to have multiple accounts across different branches, and each account must be linked to a customer profile.

**REQ-3**: The system shall allow employees to search and retrieve customer profiles using unique identifiers, such as customer ID or account number.

**REQ-4**: The system shall enable employees to update existing customer profiles, with validation checks to ensure data integrity (e.g., valid phone number format, mandatory fields).

**REQ-5**: The system shall log all actions performed on customer profiles, including creation, updates, and deletions, for audit purposes.

**REQ-6**: The system shall enforce access controls to ensure that only authorized employees can view, create, or modify customer profiles.

**REQ-7**: The system shall ensure data consistency by maintaining foreign key relationships between customer profiles and associated accounts, transactions, and loans.

**REQ-8**: The system shall validate and prevent the deletion of customer profiles that have active accounts, loans, or pending transactions.

**REQ-9**: The system shall support customer classification (individual or organization) and ensure that the appropriate fields and validation rules are applied based on the customer type.

<br>

## 4.2 Account management

### 4.2.1 Description and Priority

**Description**: The Account Management feature enables the bank to manage customer accounts, including the creation, updating, and closure of Savings, Checking, and Fixed Deposit accounts. It also includes functionalities to monitor account activities such as deposits, withdrawals, and transfers. This feature is essential for ensuring that customer accounts are properly maintained and that transactions are accurately recorded.

**Priority**: *High*

**Benefit**: 9 - Accurate and efficient management of customer accounts is critical to the bank’s operations and customer satisfaction.

**Penalty**: 9 - Errors in account management can lead to financial losses, customer dissatisfaction, and regulatory penalties.

**Cost**: 7 - Requires a robust and secure database design, with detailed tracking of account activities.

**Risk**: 8 - High risk due to the sensitivity of financial data and the need for compliance with banking regulations.

### 4.2.2 Stimulus/Response Sequences

**Stimulus**: A customer requests to open a new Savings account.
- **Response**: The system prompts the bank employee to select the appropriate Savings plan based on the customer’s eligibility (e.g., Children, Teen, Adult, Senior). The system then creates the account, sets the interest rate and minimum balance, and associates it with the customer's profile.

**Stimulus**: A customer initiates a deposit transaction.
- **Response**: The system records the deposit, updates the account balance, and logs the transaction details, including the date, amount, and branch.

**Stimulus**: A customer attempts to withdraw funds from a Savings account exceeding the monthly withdrawal limit.
- **Response**: The system denies the withdrawal, notifies the customer of the limit, and logs the attempt for auditing purposes.

**Stimulus**: A customer requests to close their account.
- **Response**: The system verifies that there are no pending transactions or outstanding loans, processes any remaining balance, and then closes the account. The system logs the closure and updates the customer profile accordingly.

**Stimulus**: A customer applies for a Fixed Deposit (FD) linked to their Savings account.
- **Response**: The system verifies the customer’s existing Savings account, creates the FD, calculates the interest based on the selected plan (e.g., 6 months, 1 year, 3 years), and schedules monthly interest deposits into the Savings account.

### 4.2.3 Functional Requirements

**REQ-1**: The system shall allow employees to create Savings, Checking, and Fixed Deposit accounts, each with specific parameters such as interest rates, withdrawal limits, and minimum balances.

**REQ-2**: The system shall enforce monthly withdrawal limits for Savings accounts and deny transactions that exceed these limits.

**REQ-3**: The system shall automatically calculate and deposit interest into Savings accounts linked to Fixed Deposits on a monthly basis.

**REQ-4**: The system shall allow employees to close accounts, with checks in place to ensure that there are no pending transactions or outstanding loans before closure.

**REQ-5**: The system shall log all account-related transactions, including deposits, withdrawals, transfers, and account closures, for auditing purposes.

**REQ-6:** The system shall support the linking of multiple accounts (Savings, Checking, FD) to a single customer profile, allowing for consolidated account management.

**REQ-7**: The system shall provide real-time balance updates and transaction histories for each account.

**REQ-8**: The system shall prevent the creation of a Fixed Deposit account unless the customer has an active Savings account.

**REQ-9**: The system shall ensure that all account actions adhere to the bank’s regulatory and operational policies, including fraud detection and anti-money laundering checks.

<br>

## 4.3 Loan Management

### 4.3.1 Description and Priority

**Description**: The Loan Management feature allows bank employees and customers to apply for and manage loans, including Business and Personal loans. It also handles the calculation of loan installments, approval workflows, and the processing of loan payments. The system supports both branch-assisted loan applications and online self-service loan applications, with specific rules for each.

**Priority**: *High*

**Benefit**: 9 - Facilitates the bank’s ability to provide and manage loans efficiently, increasing customer satisfaction and revenue.

**Penalty**: 8 - Failure to manage loans properly can lead to financial losses, customer dissatisfaction, and legal risks.

**Cost**: 7 - Requires secure and accurate handling of loan data, calculations, and approval processes.

**Risk**: 8 - High risk due to potential fraud, mismanagement, or errors in loan calculations and approvals.

### 4.3.2 Stimulus/Response Sequences

**Stimulus**: A customer applies for a Business loan at a branch.
- **Response**: The system prompts the employee to fill in the loan application details, including the loan amount, purpose, and customer financial information. The application is then submitted for approval by the branch manager.

**Stimulus**: A customer applies for a Personal loan online.
- **Response**: The system checks if the customer has an existing Fixed Deposit (FD). If eligible, the system calculates the maximum loan amount based on the FD value (up to 60% of the FD amount, with a maximum of 500,000). Upon successful submission, the loan amount is automatically credited to the customer’s Savings account.

**Stimulus**: A branch manager reviews a loan application.
- **Response**: The system presents the loan details and allows the manager to approve or reject the application. Once approved, the loan is disbursed, and the system schedules the installment payments.

**Stimulus**: A customer makes a loan installment payment.
- **Response**: The system updates the loan balance, marks the installment as paid, and generates a receipt for the customer. If the payment is late, the system may trigger additional fees or alerts.

### 4.3.3 Functional Requirements

**REQ-1**: The system shall allow employees to create and submit loan applications with all necessary details, including customer information, loan type, amount, purpose, and repayment terms.

**REQ-2**: The system shall require approval from a branch manager for branch-assisted loan applications before disbursement.

**REQ-3**: The system shall allow customers to apply for loans online, with automatic approval and disbursement based on predefined eligibility criteria (e.g., linked Fixed Deposit).

**REQ-4**: The system shall automatically calculate loan installment amounts, including interest, based on the loan amount and repayment period.

**REQ-5**: The system shall track loan payments and update the loan balance accordingly. It shall mark installments as paid when the customer makes a payment.

**REQ-6**: The system shall generate alerts for late payments and calculate any applicable late fees.

**REQ-7**: The system shall maintain a history of all loan transactions and statuses for auditing and reporting purposes.

**REQ-8**: The system shall enforce a maximum loan amount for online applications (60% of the linked FD value, with an upper limit of 500,000).

**REQ-9**: The system shall support the generation of branch-wise loan reports, including total loans disbursed, late installments, and approval rates, accessible only to branch managers.

**REQ-10**: The system shall ensure compliance with all relevant financial regulations and include measures to prevent fraud and unauthorized access.

<br>

## 4.4    Transaction Processing

### 4.4.1 Description and Priority

**Description**: The Transaction Processing feature handles all financial transactions within the bank’s Core Banking System (CBS), including deposits, withdrawals, and fund transfers between accounts. It supports both internal transactions within the same branch and transactions across different branches. This feature also includes ATM withdrawals and online fund transfers.

**Priority**: *High*

**Benefit**: 9 - Enables essential banking operations, improving customer experience and operational efficiency.

**Penalty**: 9 - Failure in transaction processing could lead to financial losses, customer dissatisfaction, and legal issues.

**Cost**: 8 - Requires secure and accurate processing of transactions with minimal downtime.

**Risk**: 8 - High risk due to the critical nature of transaction processing, potential for fraud, and the need for data consistency and security.

### 4.4.2 Stimulus/Response Sequences

**Stimulus**: A customer initiates a fund transfer to another account within the same branch.
- **Response**: The system verifies the account details, checks the balance, and processes the transfer. Both accounts are updated immediately, and a transaction receipt is generated.

**Stimulus**: A customer withdraws cash from an ATM.
- **Response**: The system checks the account balance, processes the withdrawal, updates the account, and issues a receipt. The system also records the transaction in the customer’s account history.

**Stimulus**: A customer transfers funds online to another account within the same bank.
- **Response**: The system verifies the recipient’s account, checks the sender’s balance, processes the transfer, updates both accounts, and sends a confirmation to the customer.

**Stimulus**: A customer deposits cash at a branch.
- **Response**: The system updates the customer’s account balance, generates a deposit receipt, and records the transaction in the account history.

### 4.4.3 Functional Requirements

**REQ-1**: The system shall allow customers to initiate deposits, withdrawals, and fund transfers at branches, ATMs, and through online banking.

**REQ-2**: The system shall validate account details and available balances before processing any transaction to ensure sufficient funds and prevent overdrafts.

**REQ-3**: The system shall update account balances in real-time upon the completion of a transaction.

**REQ-4**: The system shall record all transactions with a unique transaction ID, timestamp, and details of the transaction (amount, type, involved accounts, etc.).

**REQ-5**: The system shall generate receipts for all transactions, whether completed at a branch, ATM, or online.

**REQ-6**: The system shall support cross-branch fund transfers, ensuring that the correct branches are debited and credited.

**REQ-7**: The system shall implement security measures such as encryption, multi-factor authentication, and fraud detection to protect transaction integrity and customer data.

**REQ-8**: The system shall handle transaction failures gracefully, providing clear error messages and rollback mechanisms to maintain data consistency.

**REQ-9**: The system shall be able to generate transaction reports for internal auditing and customer statements, accessible by authorized personnel.

**REQ-10**: The system shall ensure compliance with all relevant banking regulations and guidelines, particularly regarding transaction limits, fees, and reporting requirements.

<br>

## 4.5 Branch Management

### 4.5.1 Description and Priority

**Description**: The Branch Management feature enables the management of all bank branches, including the head office. It handles branch-specific data, employee assignments, and roles, including branch managers and their permissions. 

**Priority**: *High*

**Benefit**: 8 - Centralized management of branches increases efficiency and ensures that operations are consistent across all locations.

**Penalty**: 7 - Poor branch management can lead to operational inefficiencies, communication breakdowns, and security risks.

**Cost**: 6 - Involves setting up secure and reliable infrastructure for branch communication and management.

**Risk**: 7 - Medium risk due to the importance of consistent management across all branches, though mitigated by existing infrastructure.

### 4.5.2 Stimulus/Response Sequences

**Stimulus**: An administrator creates a new branch in the system.
- **Response**: The system registers the new branch, assigns it a unique branch ID, and prompts the administrator to enter details such as branch manager, location, and employee assignments.

**Stimulus**: A branch manager logs into the system to manage their branch's operations.
- **Response**: The system authenticates the manager, grants access to branch-specific data, and allows the manager to view reports, manage employees, and oversee transactions.

**Stimulus**: A branch needs to connect to the head office for data synchronization.
- **Response**: The system establishes a secure connection through the leased line network, synchronizes the necessary data, and confirms the successful completion of the process.

**Stimulus**: An employee is transferred from one branch to another.
- **Response**: The system updates the employee's record, reassigns them to the new branch, and adjusts access permissions accordingly.

### 4.5.3 Functional Requirements

**REQ-1**: The system shall allow administrators to create, update, and delete branch records, including assigning branch managers and specifying branch locations.

**REQ-2**: The system shall ensure that each branch is assigned a unique branch ID, which is used in all transactions and reports to identify the branch.

**REQ-3**: The system shall provide branch managers with access to branch-specific data and management tools, including employee management and transaction oversight.

**REQ-4**: The system shall support secure, encrypted communication between branches and the head office, ensuring data integrity and confidentiality during synchronization.

**REQ-5**: The system shall allow the transfer of employees between branches, automatically updating their records and access permissions in the system.

**REQ-6**: The system shall log all changes made to branch management settings, including the creation, update, or deletion of branch records, and make these logs accessible for auditing purposes.

**REQ-7**: The system shall allow branch managers to generate and view branch-specific reports, such as transaction summaries and loan installment statuses, to assist in branch operations.

**REQ-8**: The system shall ensure compliance with all banking regulations related to branch operations, including reporting and data security standards.

<br>

## 4.6 Reporting and Analytics

### 4.6.1 Description and Priority

**Description**: The Reporting and Analytics feature provides tools for generating and viewing various reports related to branch operations and loan statuses. It includes branch-specific transaction summaries and overdue loan installment reports. Only authorized users, specifically branch managers, can access these reports. This feature aids in operational oversight and decision-making by presenting key metrics and insights.

**Priority**: *High*

**Benefit**: 9 - Essential for monitoring branch performance, ensuring compliance, and making informed management decisions.

**Penalty**: 8 - Lack of reporting can lead to missed insights, inefficiencies, and compliance issues.

**Cost**: 5 - Involves database design for report generation and implementation of access controls.

**Risk**: 6 - Medium risk due to the need for accurate data representation and secure access to sensitive information.

### 4.6.2 Stimulus/Response Sequences

**Stimulus**: A branch manager requests a branch-wise total transaction report.
- **Response**: The system generates the report based on transaction data from the branch and presents it in a readable format (e.g. Excel, PDF).

**Stimulus**: A branch manager requests a branch-wise late loan installment report.
- **Response**: The system retrieves data on overdue loan installments specific to the branch and generates a report detailing the overdue amounts and affected accounts.

**Stimulus**: A branch manager needs to filter a report by date range or account type.
- **Response**: The system allows the branch manager to specify the filter criteria and generates a report based on the selected parameters.

### 4.6.3 Functional Requirements

**REQ-1**: The system shall provide functionality for generating branch-wise total transaction reports, including details such as transaction amounts, dates, and types. The reports must be available in Excel format.

**REQ-2**: The system shall provide functionality for generating branch-wise late loan installment reports, detailing overdue amounts, affected accounts, and payment history.

**REQ-3**: The system shall implement access controls to ensure that only branch managers can view and generate reports. 

**REQ-4**: The system shall allow branch managers to filter reports by date range, account type, and other relevant parameters. 

**REQ-5**: The system shall log all report generation activities, including user details and timestamp, to maintain an audit trail for compliance and security purposes.

**REQ-6**: The system shall provide a summary of key metrics (e.g., total transactions, overdue loans) on a dashboard for quick access by branch managers.

**REQ-7**: The system shall handle errors gracefully, providing clear error messages and options for retrying or contacting support if report generation fails.

<br>

## 4.7 Additional Features

### 4.7.1 Integration with external system

#### 4.7.1.1 Description and Priority

**Description**: This feature facilitates integration with the country’s common banking switch, enabling cross-bank transfers and ATM transactions. It is crucial for ensuring compliance with new regulations and broadening the bank's service capabilities.

**Priority**: *High*

**Benefit**: 9 - Essential for regulatory compliance and expanded banking services.

**Penalty**: 8 - Lack of integration limits service offerings and regulatory compliance.

**Cost**: 7 - Involves development and testing of secure interfaces and protocols.

**Risk**: 7 - High risk due to security concerns and potential for integration issues.

#### 4.7.1.2 Stimulus/Response Sequences

**Stimulus**: A customer initiates a cross-bank transfer through the bank’s system.
- **Response**: The system sends a request to the external banking switch, processes the response, and confirms the transaction to the customer.

**Stimulus**: A customer uses an ATM to withdraw cash.
- **Response**: The ATM system communicates with the bank’s core system to authorize the withdrawal and update the customer’s account balance.

**Stimulus**: The external banking switch sends transaction data to the bank’s system for reconciliation.
- **Response**: The bank’s system processes the data, updates transaction records, and generates reconciliation reports.

**Stimulus**: An error occurs during the integration process (e.g., connection failure).
- **Response**: The system logs the error, alerts technical support, and notifies the user of the issue.

#### 4.7.1.3 Functional Requirements

**REQ-1**: The system must implement secure communication protocols to interact with the external banking switch, including encryption and authentication mechanisms.

**REQ-2**: The system must handle cross-bank transfer requests by sending appropriate messages to the external system, processing responses, and updating account balances accordingly.

**REQ-3**: The system must support ATM transactions by communicating with the external system to authorize transactions and update account records.

**REQ-4**: The system must process incoming data from the external banking switch for reconciliation purposes, updating internal records and generating necessary reports.

**REQ-5**: The system must log all integration activities and errors for auditing and troubleshooting purposes.

**REQ-6**: The system must be capable of handling errors and exceptions, providing appropriate notifications and fallback mechanisms to ensure system reliability.

<br>
<br>


# 5. Other Nonfunctional Requirements
<br>

## 5.1 Performance Requirements

-  The system must handle up to about 10,000 concurrent users. The system must have a peak load time of less than 2 seconds for any transaction-related operations.

- Database queries should return results within 1 second for most of the transactions and it should have a maximum of 2 seconds for complex queries.

- The system must support up to 500 simultaneous loan processing operations without significant degradation in performance. It should ensure that all transactions are processed within 3 seconds.

- Reports generation like branch-wise total transaction reports should not take more than 10 seconds.

<br>
## 5.2 Safety Requirements

  - The system must ensure that all transactions are atomic, consistent, isolated, and durable. In a system failure, all in-progress transactions should be rolled back to maintain data integrity.

 - Data backups must be performed daily, with a retention period of 365 days. In case of a fatal failure, the system should be recoverable within 1 hour with no data loss.

 - Safety mechanisms should prevent unauthorized access and accidental deletion of critical data. The system should be able to send alerts to administrators in case of any suspicious activity.

<br>

## 5.3 Security Requirements

 - All user access to the system must be authenticated through multi-factor authentication to ensure secure access.

 - Data must be encrypted both in transit and at rest.

 - The system should log all access and transaction activities. The logs must be retained for a minimum of 1 year to support audits and other investigations.

 - The system must comply with Seychelles’ financial regulations and data protection laws such that it ensures the protection of customer data from breaches and unauthorized access.

 - The system should implement role-based access control to limit access to sensitive data, based on the user’s role within the bank.

<br>

## 5.4 Software Quality Attributes

1. **Availability**
	- The system should be available 24/7 except for scheduled maintenance.

2. **Reliability**
	- The system should operate reliably, with a target of fewer than 5 critical failures per year. Any critical failure should be resolved within 1 hour.

3. **Maintainability**
	- The system should be designed for ease of maintenance, allowing updates, bug fixes, and patches to be applied. The maintenance period should be minimal.

 4. **Scalability**
	 - The system should be able for the addition of new branches, users, and transactions without a major rebuild of the system architecture.

5. **Usability**
	- The system should be user-friendly. It should require minimal training for employees and customers. The UI should be consistent across all platforms (desktop, web, and mobile).

<br>

## 5.5 Business Rules

 - Only branch managers can approve loan applications, with the exception of online loan requests which are automatically approved if conditions are met. 

 - Customers must have an active Savings account to open a Fixed Deposit.

 - The system should enforce interest rate and withdrawal limits as per the defined account plans.

 - Loan installments must be calculated automatically upon loan approval and adjusted if early payments are made.

 - Only branch managers can view branch-wise transaction and late loan installment reports.

<br>
<br>

# 6. Other Requirements

<br>

## 6.1 Database Requirements

The database for the online banking system must be highly available, scalable, and secure. It should support ACID properties to ensure transaction integrity. The database must enforce strong data encryption both at rest and in transit, adhering to industry standards such as AES-256. Backup and recovery mechanisms should be in place to prevent data loss. 

<br>

## 6.2 Legal Requirements

The online banking system must comply with relevant financial regulations, including:

- **GDPR** for European users to protect personal data and privacy.
- **PCI DSS** for processing and storing payment card information.
- **Anti-Money Laundering laws** to detect and prevent fraudulent activities.
- **KYC regulations** to verify the identity of customers.

All user data must be securely stored and handled according to these legal standards, and audit trails should be maintained for all transactions.


---

### Appendix A: Glossary

- **ACID**: A set of properties that guarantee database transactions are processed reliably.
- **AES-256**: Advanced Encryption Standard with a 256-bit key length used for securing data.
- **AML**: Anti-Money Laundering, a set of laws and regulations to prevent illegal money laundering activities.
- **API**: Application Programming Interface, a set of functions and protocols for building and integrating application software.
- **GDPR**: General Data Protection Regulation, a legal framework that sets guidelines for the collection and processing of personal information from individuals in the European Union (EU).
- **KYC**: Know Your Customer, a process used by banks and financial institutions to verify the identity of their clients.
- **PCI DSS**: Payment Card Industry Data Security Standard, a set of security standards designed to ensure that all companies that accept, process, store, or transmit credit card information maintain a secure environment.

---

### Appendix B: Analysis Models

#### Entity-Relationship Diagram (ERD)

![[Database Systems - Group Project - Group 6 - Page 1 2.png]]
## Group Members
Waduge S.S. - 220673K
Harinakshi W.B.S.S - 220213D
Edirisinghe E.K.K.D.R. - 220152M
Hasarinda G.S. - 220220V
Hendalage D.S.D. - 220222E

