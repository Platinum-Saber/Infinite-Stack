# Layered Architecture Style

The **Layered Architecture** (also called **n-tiered architecture**) is one of the most common architectural styles in software systems. Its popularity comes from its **simplicity**, **familiarity**, and **low cost**. It aligns well with Conway’s Law, as organizational structures (UI developers, backend developers, DBAs, etc.) naturally map into architectural layers.

---

## Topology

* Components are arranged into **horizontal layers**, each with a specific responsibility.
* Standard layers include:

  * **Presentation Layer** – handles UI and browser logic.
  * **Business Layer** – contains business rules and domain logic.
  * **Persistence Layer** – manages communication with the database.
  * **Database Layer** – the actual data store (SQL, NoSQL, or filesystem).

👉 Small apps may collapse layers (e.g., combine persistence with business), while complex systems may add extra layers like **services** or **rules**.

---

## Layers of Isolation

* **Closed Layer**: a request must pass through the layer immediately below it before moving further down.

  * Example: presentation → business → persistence → database.
* **Open Layer**: allows skipping a layer for direct access.

  * Example: presentation can directly access persistence for performance (similar to the *fast-lane reader pattern*).

**Key Principle:**

* Closed layers = better **isolation of change**.
* Isolation ensures changes in one layer don’t cascade into others, reducing brittleness.
* Layers can be replaced independently if contracts remain stable (e.g., swap JSF with React.js in presentation layer).

---

## Adding Layers

Sometimes it’s necessary to add layers for better governance:

* Example: moving **shared business objects** (utilities, logging, auditing) into a new **Services Layer**.
* Mark the services layer as **open**, so business logic can bypass it if needed, while presentation must go through it.

This prevents **tight coupling** and provides clarity on access restrictions.

---

## Other Considerations

* Often used as a **starting point architecture**, especially in early microservices efforts.
* **Anti-patterns to watch out for**:

  * **Architecture Sinkhole**: when requests pass through multiple layers without meaningful logic (just pass-through).

    * Example: presentation → business → rules → persistence → database, with each just forwarding requests.
    * Leads to performance issues and wasted processing.
  * Best practice: ensure no more than \~20% of requests are “sinkholes” (80/20 rule).

---

## Why Use This Style?

* Good **default choice** when unsure of final architecture.
* Natural fit for many **business applications**.
* Works well when teams align with technical specializations (UI, backend, DB).

---

## Architecture Characteristics Ratings

* **Simplicity**: High – easy to implement and understand.
* **Testability**: Medium – unit tests are straightforward, but integration testing across layers can be more difficult.
* **Performance**: Medium/Low – too many layers may slow down request processing.
* **Scalability**: Low/Medium – harder to scale individual layers independently.
* **Maintainability**: Medium – depends on adherence to isolation principles.
* **Flexibility**: Low – tightly bound to technical partitioning, not domains.

---

## Key Takeaways

* Layered architecture is **technically partitioned** (by role), not **domain partitioned**.
* Works best for **small to medium systems** and as a **bootstrap approach**.
* Risks: sinkhole anti-pattern, tight coupling if open/closed layers aren’t clearly documented.
* Success depends on **clear contracts** and **proper isolation**.

---
