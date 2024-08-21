# **5. Other Nonfunctional Requirements**

## 5.1 Performance Requirements

-  The system must handle up to about 20,000 concurrent users. The system must have a peak load time of less than 2 seconds for any transaction-related operations.

- Database queries should return results within 1 second for most of the transactions and it should have a maximum of 2 seconds for complex queries.

- The system must support up to 500 simultaneous loan processing operations without significant degradation in performance. It should ensure that all transactions are processed within 3 seconds.

- Reports generation like branch-wise total transaction reports should not take more than 10 seconds.

## 5.2 Safety Requirements

  - The system must ensure that all transactions are atomic, consistent, isolated, and durable. In a system failure, all in-progress transactions should be rolled back to maintain data integrity.

 - Data backups must be performed daily, with a retention period of 365 days. In case of a fatal failure, the system should be recoverable within 1 hour with no data loss.

 - Safety mechanisms should prevent unauthorized access and accidental deletion of critical data. The system should be able to send alerts to administrators in case of any suspicious activity.

## 5.3 Security Requirements

 - All user access to the system must be authenticated through multi-factor authentication to ensure secure access.

 - Data must be encrypted both in transit and at rest.

 - The system should log all access and transaction activities. The logs must be retained for a minimum of 1 year to support audits and other investigations.

 - The system must comply with Seychelles’ financial regulations and data protection laws such that it ensures the protection of customer data from breaches and unauthorized access.

 - The system should implement role-based access control to limit access to sensitive data, based on the user’s role within the bank.

## 5.4 Software Quality Attributes

1. **Availability**
	- The system should be available 24/7 except for scheduled maintenance.

2. **Reliability**
	- The system should operate reliably, with a target of fewer than 5 critical failures per year. Any critical failure should be resolved within 1 hour.

1. **Maintainability**
	- The system should be designed for ease of maintenance, allowing updates, bug fixes, and patches to be applied. The maintenance period should be minimal.

 4. **Scalability**
- The system should be able for the addition of new branches, users, and transactions without a major rebuild of the system architecture.

5. **Usability**
- The system should be user-friendly. It should require minimal training for employees and customers. The UI should be consistent across all platforms (desktop, web, and mobile).

6. **Interoperability:** (mekt wen namak thyenwnm dann. Chatgpt apu ekak)
- The system should be designed to integrate seamlessly with the country’s common banking switch. It should adhere to the required API standards and protocols.

## 5.5 Business Rules

 - Only branch managers can approve loan applications, with the exception of online loan requests which are automatically approved if conditions are met. (automatically approve????)

 - Customers must have an active Savings account to open a Fixed Deposit.

 - The system should enforce interest rate and withdrawal limits as per the defined account plans.

 - Loan installments must be calculated automatically upon loan approval and adjusted if early payments are made.

 - Only branch managers can view branch-wise transaction and late loan installment reports.