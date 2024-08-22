# 4. System Features

## 4.1    Customer management

### 4.1.1 Description and Priority

**Description**: The Customer Management feature allows the bank to manage customer data, including the creation, updating, and deletion of customer profiles. It supports the classification of customers as either individuals or organizations (e.g., NGOs, companies), and handles the association of customers with multiple accounts across different branches.

**Priority**: *High*

**Benefit**: 9 - Ensures that accurate customer data is maintained, which is critical for all banking operations.

**Penalty**: 8 - Inconsistent or incorrect customer data can lead to errors in transactions, account management, and loan processing.

**Cost:** 6 - Involves designing a robust database structure and secure access controls.

**Risk**: 7 - Data integrity and security are paramount, as customer data is sensitive and must comply with regulations.

## 4.1.2 Stimulus/Response Sequences

**Stimulus**: A customer visits a branch to open a new account.
- **Response**: The system prompts the bank employee to create a new customer profile by entering personal or organizational details, such as name, address, and identification information. Once the profile is created, the customer can proceed to open an account.

**Stimulus**: A customer requests to update their personal details, such as address or phone number.
- **Response**: The system allows the bank employee to search for the customer profile and update the necessary information. The system saves the changes and logs the update.

**Stimulus**: A bank employee needs to retrieve a customer’s profile for verification during a transaction.
- **Response**: The system searches the database based on customer ID or other identifiers, retrieves the profile, and displays it for the employee’s review.

**Stimulus**: A customer requests to close their account and delete their profile.
- **Response**: The system verifies that the customer has no pending transactions or obligations (e.g., loans), and then proceeds to deactivate the profile and associated accounts.

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
