
## Project Overview
- The Goalkeeper Robot is designed to guard a **9ft × 6ft football goalpost**.  
- The robot is mounted at the **center of the goal**, capable of **rotating using a NEMA 32 servo motor** to block incoming balls.  
- A **depth camera** will be used to track the ball/player, perform predictive analysis, and control the servo system in real-time.

---

## Project Stages & Timeline (3 Weeks)

### Week 1
#### Stage 1: Servo Motor Setup (3 days)
- Install and test **NEMA 32 servo motor** with driver.
- Implement basic angle rotation control.
- Verify accurate and fast response to position commands.

---

#### Stage 2: Camera Setup & Data Acquisition (4 days)
- Install **Orbbec Astra Pro drivers**.
- Write Python scripts to acquire **RGB + Depth data**.
- Visualize player movement and ball trajectory.

---

### Week 2
#### Stage 3: Predictive Analysis (4 days)
- Implement trajectory prediction algorithm using depth data.
- Test ball tracking under different speeds and angles.

#### Stage 4: Integration with Servo System (3 days)
- Connect predictive output to servo controller.
- Test full system: ball detection → trajectory prediction → servo movement.
- Optimize latency and accuracy.

### Week 3
#### Stage 5: Testing and Debugging

---
![[Pasted image 20250915222047.png]]
## Components Required

| Component                                                      | Quantity | Estimated Cost | Links                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             |
| -------------------------------------------------------------- | -------- | -------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| NEMA 32 Servo Motor (with driver)                              | 1        | Rs. 58 000/=   | [Servo Motor Driver Kit Magnetic](https://www.aliexpress.com/item/1005009132424377.html?spm=a2g0o.productlist.main.8.72e9lSiBlSiBKS&algo_pvid=a6c0afdb-5102-4bd5-b6b6-01fd2ef29546&aem_p4p_detail=2025091509353610285555692752300004725998&algo_exp_id=a6c0afdb-5102-4bd5-b6b6-01fd2ef29546-7&pdp_ext_f=%7B%22order%22%3A%228%22%2C%22eval%22%3A%221%22%7D&pdp_npi=6%40dis%21LKR%2154866.56%2136760.78%21%21%211155.83%21774.41%21%402101590d17579541366665501ea2ae%2112000048028267526%21sea%21LK%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3A4f563db5%3Bm03_new_user%3A-29895&curPageLogUid=trSWSSGAFJzZ&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005009132424377%7C_p_origin_prod%3A&search_p4p_id=2025091509353610285555692752300004725998_2) |
| Servo Motor Mount + Coupling                                   | 1 set    | Rs. 5000/=     |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   |
| Orbbec Astra Pro Depth Camera (used for prototype and testing) | 1        | Available      |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   |
| Power Supply (24V, 10A)                                        | 1        | Rs. 10000/=    |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   |
| Control PC (Laptop)                                            | 1        | Available      |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   |
| Misc. (Cables, Mounts, Frame, floor board, etc)                | -        | Rs. 20 000/=   |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   |
| Orbbec Gemini 2L (Replaces Astra pro)                          | 1        | Rs. 140 000    | [ORBBEC Gemini 2L depth camera](https://www.aliexpress.com/item/1005008694199910.html?spm=a2g0o.productlist.main.7.66333260RSaGmh&algo_pvid=f4996f24-e128-4f1f-8b8c-729173ac9f8e&algo_exp_id=f4996f24-e128-4f1f-8b8c-729173ac9f8e-6&pdp_ext_f=%7B%22order%22%3A%221%22%2C%22eval%22%3A%221%22%7D&pdp_npi=6%40dis%21LKR%21118578.56%21118578.56%21%21%212498.00%212498.00%21%400b1bf20a17579580561628775e7a57%2112000046276137337%21sea%21LK%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3A4f563db5%3Bm03_new_user%3A-29895&curPageLogUid=o0zT25mOfS3P&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005008694199910%7C_p_origin_prod%3A)                                                                                                                 |


---


