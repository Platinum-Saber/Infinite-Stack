---
tags: 
Created: 2025-02-19 10:49
About: 
Reviewed: false
Completion: 0
---

## Status
Reviewed : `INPUT[toggle:Reviewed]`

Progress :  
```meta-bind
INPUT[progressBar:Completion]
```

# Diagrams

**University Canteen Food Reservation System**

1. **Use Case Diagram**
    
    - Actors: Student, Canteen Staff, System Admin
    - Use Cases: Place Order, Cancel Order, View Menu, Payment Processing, Order Pickup Notification
2. **Class Diagram**
    
    - Classes: User, Student, Staff, Order, Menu, Payment, Notification
    - Relationships: Student places Order, Order has MenuItems, Staff processes Order
3. **Sequence Diagram** (For Order Placement)
    
    - Student selects food -> System verifies availability -> Student confirms order -> System processes payment -> Order confirmation sent
4. **Activity Diagram** (Order Workflow)
    
    - Start -> Select Menu Items -> Place Order -> Payment -> Order Confirmed -> Pickup Notification -> End
5. **State Diagram** (Order State Transitions)
    
    - Ordered -> Processed -> Ready for Pickup -> Completed
6. **Component Diagram**
    
    - Web Application, Database, Payment Gateway, Notification System
7. **Deployment Diagram**
    
    - Server hosting web app, database server, payment gateway server

---

**University Canteen Inventory Management System**

1. **Use Case Diagram**
    
    - Actors: Canteen Manager, Staff
    - Use Cases: Add Stock, Update Stock, Remove Stock, View Inventory, Generate Report
2. **Class Diagram**
    
    - Classes: Inventory, Item, Supplier, Report, Staff
3. **Sequence Diagram** (For Adding Stock)
    
    - Staff inputs stock details -> System validates -> Stock updated -> Confirmation sent
4. **Activity Diagram**
    
    - Start -> Select Item -> Add/Update Quantity -> Confirm Changes -> Update Inventory -> End
5. **State Diagram** (Item Lifecycle)
    
    - Available -> Low Stock -> Out of Stock -> Replenished
6. **Component Diagram**
    
    - Inventory Management System, Database, Report Generator
7. **Deployment Diagram**
    
    - Web App, Central Inventory Database

---

**University Library Book Lending and Reservation System**

1. **Use Case Diagram**
    
    - Actors: Student, Librarian
    - Use Cases: Borrow Book, Return Book, Reserve Book, View Catalog, Manage Fines
2. **Class Diagram**
    
    - Classes: Book, User, Student, Librarian, Transaction, Fine
3. **Sequence Diagram** (For Book Borrowing)
    
    - Student searches -> Selects book -> Checks availability -> System logs transaction -> Book issued
4. **Activity Diagram**
    
    - Start -> Search Book -> Reserve/Borrow -> Confirm Action -> Update System -> End
5. **State Diagram** (Book Lifecycle)
    
    - Available -> Borrowed -> Reserved -> Returned
6. **Component Diagram**
    
    - Library Management System, Database, Payment Gateway
7. **Deployment Diagram**
    
    - Library System Server, Database Server

---

**University Infrastructure Reservation System for Events**

1. **Use Case Diagram**
    
    - Actors: Student, Staff, Admin
    - Use Cases: Reserve Space, Cancel Reservation, Approve Requests, View Availability
2. **Class Diagram**
    
    - Classes: User, Reservation, Venue, Admin
3. **Sequence Diagram** (For Reserving Space)
    
    - User selects venue -> Checks availability -> Confirms reservation -> System logs booking
4. **Activity Diagram**
    
    - Start -> Select Venue -> Check Availability -> Confirm Reservation -> Notify User -> End
5. **State Diagram**
    
    - Available -> Reserved -> Approved -> Cancelled
6. **Component Diagram**
    
    - Venue Booking System, Notification System, Database
7. **Deployment Diagram**
    
    - Server hosting booking system, notification service

---

**CSE Mentoring Program Progress Monitoring and Management System**

1. **Use Case Diagram**
    
    - Actors: Mentor, Mentee, Admin
    - Use Cases: Assign Mentor, Log Progress, View Reports, Schedule Meeting
2. **Class Diagram**
    
    - Classes: Mentor, Mentee, Session, ProgressReport
3. **Sequence Diagram** (For Logging Progress)
    
    - Mentor inputs progress -> System validates -> Updates record -> Generates report
4. **Activity Diagram**
    
    - Start -> Assign Mentor -> Log Progress -> Update System -> Generate Report -> End
5. **State Diagram**
    
    - Not Started -> In Progress -> Completed
6. **Component Diagram**
    
    - Mentorship Management System, Database, Reporting Service
7. **Deployment Diagram**
    
    - Mentorship Portal, Database Server

---

_This document contains UML diagrams for all requested university systems. Please review and let me know if you need modifications before generating the final PDF._





