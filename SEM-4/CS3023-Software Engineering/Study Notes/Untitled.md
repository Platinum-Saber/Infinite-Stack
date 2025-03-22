---
tags: 
Created: 2025-02-19 11:06
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

# Activity Diagram

```mermaid
stateDiagram-v2
    [*] --> Login
    Login --> ViewMenu
    ViewMenu --> SelectItems
    SelectItems --> AddToCart
    AddToCart --> ModifyCart
    ModifyCart --> SelectItems: Add More Items
    ModifyCart --> ChoosePayment: Proceed to Checkout
    ChoosePayment --> ProcessPayment
    ProcessPayment --> PaymentFailed: Payment Error
    PaymentFailed --> ChoosePayment
    ProcessPayment --> OrderConfirmed: Payment Success
    OrderConfirmed --> [*]

    state ModifyCart {
        [*] --> UpdateQuantity
        UpdateQuantity --> RemoveItems
        RemoveItems --> [*]
    }
```


# Use Case Diagram

```mermaid
---
title: University Canteen Food Reservation System - Use Case Diagram
---
flowchart LR
    %% Define actors properly
    Student(["🧑‍🎓 Student"])
    Staff(["🧑‍💼 Staff"])
    Cashier(["💰 Cashier"])
    Kitchen(["👨‍🍳 Kitchen Staff"])
    Admin(["🛠️ Admin"])

    subgraph System["Food Reservation System"]
        Login["Login/Register"]
        ViewMenu["View Menu"]
        PlaceOrder["Place Order"]
        Payment["Make Payment"]
        ManageProfile["Manage Profile"]
        ViewHistory["View Order History"]
        UpdateMenu["Update Menu"]
        PrepareFood["Prepare Food"]
        ProcessOrder["Process Order"]
        ManageUsers["Manage Users"]
        Reports["Generate Reports"]
    end

    %% Connect actors to use cases
    Student --> Login
    Student --> ViewMenu
    Student --> PlaceOrder
    Student --> Payment
    Student --> ManageProfile
    Student --> ViewHistory

    Staff --> Login
    Staff --> ViewMenu
    Staff --> PlaceOrder
    Staff --> Payment
    Staff --> ViewHistory

    Cashier --> Login
    Cashier --> ProcessOrder
    Cashier --> Payment

    Kitchen --> Login
    Kitchen --> PrepareFood
    Kitchen --> UpdateMenu

    Admin --> Login
    Admin --> ManageUsers
    Admin --> Reports
    Admin --> UpdateMenu


```

# Sequence Diagram

```mermaid
sequenceDiagram
    actor Student
    participant UI as User Interface
    participant Auth as Authentication
    participant Menu as Menu Service
    participant Order as Order Service
    participant Payment as Payment Service
    participant Kitchen as Kitchen Service

    Student->>UI: Access System
    UI->>Auth: Verify Credentials
    Auth-->>UI: Authentication Success
    Student->>UI: Request Menu
    UI->>Menu: Get Available Items
    Menu-->>UI: Return Menu Items
    Student->>UI: Place Order
    UI->>Order: Create Order
    Order->>Payment: Process Payment
    Payment-->>Order: Payment Confirmation
    Order->>Kitchen: Send Order
    Kitchen-->>Order: Order Received
    Order-->>UI: Order Confirmation
    UI-->>Student: Display Confirmation
```


# Class Diagram

```mermaid
classDiagram
    class User {
        +int userID
        +String name
        +String email
        +String password
        +String role
        +login()
        +logout()
        +updateProfile()
    }

    class Student {
        +String studentID
        +float balance
        +viewOrderHistory()
        +makePayment()
    }

    class MenuItem {
        +int itemID
        +String name
        +float price
        +String description
        +String category
        +boolean available
        +updateAvailability()
        +updatePrice()
    }

    class Order {
        +int orderID
        +int userID
        +DateTime orderTime
        +float totalAmount
        +String status
        +createOrder()
        +updateStatus()
        +cancelOrder()
    }

    class OrderItem {
        +int orderItemID
        +int orderID
        +int itemID
        +int quantity
        +float subtotal
        +calculateSubtotal()
    }

    class Payment {
        +int paymentID
        +int orderID
        +float amount
        +String paymentMethod
        +DateTime paymentTime
        +String status
        +processPayment()
        +generateReceipt()
    }

    User <|-- Student
    Order "1" *-- "many" OrderItem
    OrderItem "many" o-- "1" MenuItem
    Order "1" -- "1" Payment
    Student "1" -- "many" Order
```

# State Diagram

```mermaid
stateDiagram-v2
    [*] --> Created
    Created --> PaymentPending: Order Placed
    PaymentPending --> PaymentFailed: Payment Error
    PaymentPending --> Confirmed: Payment Successful
    PaymentFailed --> PaymentPending: Retry Payment
    PaymentFailed --> Cancelled: Cancel Order
    Confirmed --> InPreparation: Kitchen Accepts
    InPreparation --> Ready: Food Prepared
    Ready --> Completed: Order Collected
    Cancelled --> [*]
    Completed --> [*]

    note right of PaymentPending
        Payment must be completed
        within 15 minutes
    end note

    note right of Ready
        Order must be collected
        within 30 minutes
    end note
```

