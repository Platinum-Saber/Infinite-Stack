Here are 20 multiple-choice questions (MCQs) based on the provided PDF about relational database design, formatted in markdown according to the style found in your previous file:

---

# Relational Database Design: MCQ Test

> [!dbq]- Question 1
> >[!faq]- What is a functional dependency in relational database design? 
> > - [ ] a) A relationship between multiple databases
> > - [ ] b) A constraint between two attributes in a database
> > - [ ] c) A set of rules to delete redundant data
> > - [ ] d) A way to uniquely identify tuples in a relation
> 
> >[!success]- Answer  
> >- b) A constraint between two attributes in a database

> [!dbq]- Question 2
> >[!faq]- **Which normal form ensures no partial dependencies exist?**
> > 
> > - [ ] a) 1NF
> > - [ ] b) 2NF
> > - [ ] c) 3NF
> > - [ ] d) BCNF
> 
> >[!success]- Answer  
> >- b) 2NF


>[!dbq]- Question 3
> >[!faq]- In First Normal Form (1NF), a relation must have:
> > 
> > - [ ] a) Non-trivial functional dependencies
> > - [ ] b) Atomic attributes
> > - [ ] c) Foreign keys
> > - [ ] d) No multivalued attributes
> 
>> [!success]- Answer  
>>-  b) Atomic attributes


> [!dbq]- Question 4
> >[!faq]- What is the goal of normalization in relational database design?
> > - [ ] a) To increase redundancy in the database
> > - [ ] b) To reduce redundancy and prevent anomalies
> > - [ ] c) To add more attributes to each relation
> > - [ ] d) To improve the performance of all queries
> 
>> [!success]- Answer  
>>-  b) To reduce redundancy and prevent anomalies


> [!dbq]- Question 5
>> [!faq]- Which of the following is a characteristic of Boyce-Codd Normal Form (BCNF)?
> > 
> > - [ ] a) Every attribute is a primary key
> > - [ ] b) Every non-trivial functional dependency has a superkey on the left-hand side
> > - [ ] c) It only applies to composite keys
> > - [ ] d) It allows transitive dependencies
> 
>> [!success]- Answer  
>>- b) Every non-trivial functional dependency has a superkey on the left-hand side


> [!dbq]- Question 6
> >[!faq]- What is an extraneous attribute in a functional dependency?
> > 
> > - [ ] a) An attribute that is part of the primary key
> > - [ ] b) An attribute that can be removed without changing the closure of the functional dependency
> > - [ ] c) An attribute that uniquely identifies tuples in a relation
> > - [ ] d) An attribute that is always present in every tuple
> 
> 
>> [!success]- Answer  
>>- b) An attribute that can be removed without changing the closure of the functional dependency


> [!dbq]- Question 7
>> [!faq]- Which normal form is concerned with removing multivalued dependencies?
> > 
> > - [ ] a) 3NF
> > - [ ] b) 2NF
> > - [ ] c) 4NF
> > - [ ] d) BCNF
> 
>> [!success]- Answer  
>>-  c) 4NF


> [!dbq]- Question 8
> >[!faq]- What is the purpose of a lossless-join decomposition?
> > 
> > - [ ] a) To eliminate transitive dependencies
> > - [ ] b) To ensure that no data is lost when relations are decomposed
> > - [ ] c) To normalize a database to BCNF
> > - [ ] d) To reduce the size of the relations
> 
>> [!success]- Answer  
>>-  b) To ensure that no data is lost when relations are decomposed


> [!dbq]- Question 9
> >[!faq]- In the context of functional dependencies, what does the closure of an attribute set represent?
> > 
> > - [ ] a) The minimal set of attributes that functionally determines the relation
> > - [ ] b) The set of all attributes that can be functionally determined by the attribute set
> > - [ ] c) The keys of the relation
> > - [ ] d) The set of attributes that are part of the foreign keys
> 
> >[!success]- Answer  
> >- b) The set of all attributes that can be functionally determined by the attribute set


> [!dbq]- Question 10
> >[!faq]- A decomposition is dependency preserving if:
> > 
> > - [ ] a) Every relation in the decomposition contains all the functional dependencies of the original relation
> > - [ ] b) Every functional dependency in the original schema is maintained in the decomposition
> > - [ ] c) There are no multivalued attributes in any relation
> > - [ ] d) The decomposition includes all candidate keys
> 
> >[!success]- Answer  
> >- b) Every functional dependency in the original schema is maintained in the decomposition


> [!dbq]- Question 11
> >[!faq]- What does it mean for a relation to be in Third Normal Form (3NF)?
> > 
> > - [ ] a) The relation has no transitive dependencies
> > - [ ] b) The relation has no non-atomic attributes
> > - [ ] c) Every non-prime attribute is fully dependent on every candidate key
> > - [ ] d) The relation has no redundant data
> 
> >[!success]- Answer  
> >- a) The relation has no transitive dependencies


> [!dbq]- Question 12
> >[!faq]- What is a canonical cover in the context of functional dependencies?
> > 
> > - [ ] a) A minimal set of attributes that forms a key
> > - [ ] b) A minimal set of functional dependencies that is equivalent to the original set
> > - [ ] c) A set of attributes that covers all candidate keys
> > - [ ] d) A set of relations that is normalized to BCNF
> 
>> [!success]- Answer  
>>-  b) A minimal set of functional dependencies that is equivalent to the original set


> [!dbq]- Question 13
> > [!faq]- What is a superkey?
> > 
> > - [ ] a) A set of attributes that uniquely identifies a tuple in a relation
> > - [ ] b) A candidate key with only one attribute
> > - [ ] c) A foreign key that references another relation
> > - [ ] d) An attribute that can be null
> 
> >[!success]- Answer  
> >- a) A set of attributes that uniquely identifies a tuple in a relation


> [!dbq]- Question 14
> >[!faq]- Which of the following statements is true for BCNF?
> > 
> > - [ ] a) Every relation in BCNF is also in 2NF and 3NF
> > - [ ] b) BCNF allows partial dependencies
> > - [ ] c) BCNF only applies to relations with composite keys
> > - [ ] d) A relation in BCNF must have a foreign key
> 
> >[!success]- Answer  
> >- a) Every relation in BCNF is also in 2NF and 3NF



> [!dbq]- Question 15
> Which functional dependency holds in the relation `Instructor(ID, Name, Dept)` if each instructor belongs to one department?
> 
> - [ ] a) Dept → ID
> - [ ] b) ID → Dept
> - [ ] c) Name → ID
> - [ ] d) Dept → Name
> 
> [!success] - Answer  
> b) ID → Dept



> [!dbq]- Question 16
> What is the purpose of a decomposition algorithm in database design?
> 
> - [ ] a) To normalize a relation while preserving functional dependencies and ensuring a lossless-join
> - [ ] b) To increase the number of relations in the schema
> - [ ] c) To eliminate all candidate keys in a relation
> - [ ] d) To create multivalued attributes
> 
> [!success] - Answer  
> a) To normalize a relation while preserving functional dependencies and ensuring a lossless-join



> [!dbq]- Question 17
> Which of the following is not a characteristic of 4NF?
> 
> - [ ] a) It removes multivalued dependencies
> - [ ] b) It allows for transitive dependencies
> - [ ] c) It extends BCNF
> - [ ] d) It is violated by a multivalued dependency
> 
> [!success] - Answer  
> b) It allows for transitive dependencies



> [!dbq]- Question 18
> Which relational algebra operation combines rows from two relations based on a common attribute?
> 
> - [ ] a) Union
> - [ ] b) Selection
> - [ ] c) Join
> - [ ] d) Projection
> 
> [!success] - Answer  
> c) Join



> [!dbq]- Question 19
> What is an example of a transitive dependency in a relation?
> 
> - [ ] a) A → B, B → C, so A → C
> - [ ] b) A → B, A → C
> - [ ] c) A → A, B → B
> - [ ] d) A → C, C → A
> 
> [!success] - Answer  
> a) A → B, B → C, so A → C



>[!dbq]- Question 20
> >[!faq]- Which of the following anomalies can occur when a relation is not normalized?
> > 
> > - [ ] a) Insertion, Update, Deletion anomalies
> > - [ ] b) Redundancy anomalies
> > - [ ] c) Foreign key anomalies
> > - [ ] d) Primary key anomalies
> 
>> [!success]- Answer  
>> a) Insertion, Update, Deletion anomalies

--- 

This set of questions is designed to test foundational concepts in relational database design, including normalization, functional dependencies, and relational algebra operations.