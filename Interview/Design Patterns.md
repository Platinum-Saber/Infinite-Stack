
# Design Patterns — Descriptive Notes (with Java examples, use cases, benefits & disadvantages)

> [!abstract] Overview
> A practical guide to **Gang of Four** design patterns with:  
> • **Description** • **Use cases** • **Benefits** • **Disadvantages** • **Java examples**  
> Organized into **Creational**, **Structural**, and **Behavioral** families.

---

## Pattern Map

> [!table] Families
> | Family | Patterns |
> |---|---|
> | **Creational** | Singleton, Factory Method, Abstract Factory, Builder, Prototype |
> | **Structural** | Adapter, Bridge, Composite, Decorator, Facade, Flyweight, Proxy |
> | **Behavioral** | Strategy, Observer, Command, Iterator, Mediator, Memento, State, Template Method, Visitor, Chain of Responsibility |

---

## Part I — Creational Patterns

### 1) Singleton
**Description.** Ensure exactly one instance of a class and provide a global access point.  
**Use cases.** App configuration, loggers, caches, connection pools.  
**Benefits.** Controlled access to a single resource; lazy initialization possible.  
**Disadvantages.** Hidden global state; hard to test/mock; potential bottleneck.

**Java (thread‑safe holder idiom)**

```java
final class AppConfig {
    private AppConfig() {}
    private static class Holder { static final AppConfig INSTANCE = new AppConfig(); }
    public static AppConfig getInstance() { return Holder.INSTANCE; }
}
```

---

### 2) Factory Method
**Description.** Let subclasses (or injected factories) decide which concrete product to create.  
**Use cases.** UI widgets per platform; parsers by file type; transport per protocol.  
**Benefits.** Decouples client from concrete classes; open for extension.  
**Disadvantages.** More classes/indirection; can be overkill for simple creation.

**Java**

```java
interface Button { void render(); }
class WindowsButton implements Button { public void render(){ System.out.println("WinBtn"); } }
class LinuxButton implements Button  { public void render(){ System.out.println("LinBtn"); } }

abstract class Dialog {
    public void show() { Button b = createButton(); b.render(); }
    protected abstract Button createButton();
}
class WindowsDialog extends Dialog { protected Button createButton(){ return new WindowsButton(); } }
class LinuxDialog   extends Dialog { protected Button createButton(){ return new LinuxButton(); } }
```

---

### 3) Abstract Factory
**Description.** Create **families of related objects** without specifying their concrete classes.  
**Use cases.** Cross‑platform UI kits; skin/theme packs; database vendor portability.  
**Benefits.** Ensures products match; centralizes family switching.  
**Disadvantages.** Adding new product types requires changing all factories.

**Java**

```java
interface UIIcon { String name(); }
interface UIButton { void render(); }
interface UIFactory {
    UIIcon createIcon();
    UIButton createButton();
}
class WinFactory implements UIFactory {
    public UIIcon createIcon(){ return () -> "WinIcon"; }
    public UIButton createButton(){ return () -> System.out.println("WinBtn"); }
}
class MacFactory implements UIFactory {
    public UIIcon createIcon(){ return () -> "MacIcon"; }
    public UIButton createButton(){ return () -> System.out.println("MacBtn"); }
}
```

---

### 4) Builder
**Description.** Separate construction of a complex object from its representation; build step‑by‑step.  
**Use cases.** Immutable objects with many optional fields; query builders; HTTP requests.  
**Benefits.** Readable fluent APIs; immutability; validation before build.  
**Disadvantages.** Boilerplate for simple objects; extra classes.

**Java**

```java
class HttpRequest {
    final String method, url, body;
    final int timeoutMs;
    private HttpRequest(Builder b){
        this.method=b.method; this.url=b.url; this.body=b.body; this.timeoutMs=b.timeoutMs;
    }
    static class Builder {
        String method="GET", url, body=""; int timeoutMs=3000;
        Builder method(String m){ this.method=m; return this; }
        Builder url(String u){ this.url=u; return this; }
        Builder body(String b){ this.body=b; return this; }
        Builder timeout(int t){ this.timeoutMs=t; return this; }
        HttpRequest build(){ return new HttpRequest(this); }
    }
}
```

---

### 5) Prototype
**Description.** Create new objects by cloning existing ones.  
**Use cases.** Expensive initialization; copying object graphs; undo buffers.  
**Benefits.** Avoids re‑initialization cost; runtime object composition.  
**Disadvantages.** Deep vs shallow copy pitfalls; clone contract complexity.

**Java**

```java
class Shape implements Cloneable {
    int x, y; String color;
    public Shape(int x,int y,String c){ this.x=x; this.y=y; this.color=c; }
    public Shape clone() {
        try { return (Shape) super.clone(); }
        catch (CloneNotSupportedException e){ throw new AssertionError(); }
    }
}
```

---

## Part II — Structural Patterns

### 6) Adapter
**Description.** Convert one interface into another that clients expect.  
**Use cases.** Wrapping legacy/third‑party APIs; mismatched interfaces.  
**Benefits.** Reuse existing code without changing it; decouples client from adaptee.  
**Disadvantages.** Extra layer; potential performance overhead.

**Java**

```java
interface JsonStore { void put(String key, String json); }
class LegacyKV { public void set(String k, byte[] v) { /*...*/ } }

class JsonStoreAdapter implements JsonStore {
    private final LegacyKV kv;
    JsonStoreAdapter(LegacyKV kv){ this.kv = kv; }
    public void put(String key, String json) { kv.set(key, json.getBytes()); }
}
```

---

### 7) Bridge
**Description.** Decouple abstraction from implementation so both can vary independently.  
**Use cases.** Cross‑product hierarchies (Shape×Renderer, View×Platform).  
**Benefits.** Avoids class explosion; mix‑and‑match abstractions/implementations.  
**Disadvantages.** More indirection; requires disciplined design.

**Java**

```java
interface Renderer { void drawCircle(float x,float y,float r); }
class VectorRenderer implements Renderer { public void drawCircle(float x,float y,float r){ System.out.println("Vector circle"); } }
class RasterRenderer implements Renderer { public void drawCircle(float x,float y,float r){ System.out.println("Raster circle"); } }

abstract class Shape {
    protected final Renderer r;
    protected Shape(Renderer r){ this.r = r; }
}
class Circle extends Shape {
    float x,y,rad;
    Circle(Renderer r, float x,float y,float rad){ super(r); this.x=x; this.y=y; this.rad=rad; }
    void draw(){ r.drawCircle(x,y,rad); }
}
```

---

### 8) Composite
**Description.** Compose objects into tree structures to treat part‑whole uniformly.  
**Use cases.** GUIs, file systems, scene graphs, organization charts.  
**Benefits.** Uniform client code for leaf and composite; scalable hierarchies.  
**Disadvantages.** Harder to enforce constraints; over‑generalization risks.

**Java**

```java
import java.util.*;
interface Graphic { void draw(); }
class Dot implements Graphic { public void draw(){ System.out.println("Dot"); } }
class CompoundGraphic implements Graphic {
    private final List<Graphic> children = new ArrayList<>();
    public void add(Graphic g){ children.add(g); }
    public void draw(){ children.forEach(Graphic::draw); }
}
```

---

### 9) Decorator
**Description.** Attach additional responsibilities to objects dynamically via wrapping.  
**Use cases.** I/O filters; cross‑cutting concerns (encryption, compression, caching).  
**Benefits.** Combinatorial flexibility without subclass explosion.  
**Disadvantages.** Many small objects; debugging can be harder.

**Java**

```java
interface DataSource { void write(String data); }
class FileDataSource implements DataSource {
    public void write(String data){ System.out.println("Write: "+data); }
}
class EncryptionDecorator implements DataSource {
    private final DataSource wrap;
    EncryptionDecorator(DataSource ds){ this.wrap=ds; }
    public void write(String data){ wrap.write("enc(" + data + ")"); }
}
```

---

### 10) Facade
**Description.** Provide a simple, unified API over a complex subsystem.  
**Use cases.** Simplify third‑party libraries; common workflows; onboarding.  
**Benefits.** Shields clients from complexity; reduces coupling.  
**Disadvantages.** Risk of god‑object; can hide needed features.

**Java**

```java
class VideoDecoder { void open(String f){} void decode(){} }
class AudioDecoder { void open(String f){} void decode(){} }
class MediaFacade {
    private final VideoDecoder v = new VideoDecoder();
    private final AudioDecoder a = new AudioDecoder();
    void play(String file){ v.open(file); a.open(file); v.decode(); a.decode(); }
}
```

---

### 11) Flyweight
**Description.** Share intrinsic state to support many fine‑grained objects efficiently.  
**Use cases.** Text editors (glyphs), game tiles/particles, map markers.  
**Benefits.** Huge memory savings; faster creation.  
**Disadvantages.** Complex state split (intrinsic vs extrinsic); thread‑safety.

**Java**

```java
import java.util.*;
class Glyph {
    private final char ch;
    private Glyph(char ch){ this.ch=ch; }
    static class Factory {
        private static final Map<Character,Glyph> pool = new HashMap<>();
        static Glyph get(char c){ return pool.computeIfAbsent(c, Glyph::new); }
    }
}
```

---

### 12) Proxy
**Description.** Stand‑in object controlling access to a real subject (remote, virtual, protection, caching).  
**Use cases.** Lazy loading, access control, remote service stubs, caching.  
**Benefits.** Performance (lazy/caching), security, distribution transparency.  
**Disadvantages.** Added latency; complexity; need to mirror interface.

**Java**

```java
interface Image { void display(); }
class RealImage implements Image {
    private final String path;
    RealImage(String p){ path=p; loadFromDisk(); }
    private void loadFromDisk(){ System.out.println("Loading " + path); }
    public void display(){ System.out.println("Displaying " + path); }
}
class LazyImageProxy implements Image {
    private final String path; private RealImage real;
    LazyImageProxy(String p){ path=p; }
    public void display(){
        if(real==null) real = new RealImage(path);
        real.display();
    }
}
```

---

## Part III — Behavioral Patterns

### 13) Strategy
**Description.** Define a family of algorithms, encapsulate each, and make them interchangeable.  
**Use cases.** Pricing rules, sorting strategies, compression/encryption options.  
**Benefits.** Eliminates conditionals; open/closed; swap at runtime.  
**Disadvantages.** More classes; selection logic still needed somewhere.

**Java**

```java
interface PricingStrategy { double price(double base); }
class NormalPrice implements PricingStrategy { public double price(double base){ return base; } }
class HolidayDiscount implements PricingStrategy { public double price(double base){ return base * 0.8; } }
class Cart {
    private PricingStrategy ps;
    Cart(PricingStrategy ps){ this.ps=ps; }
    void setStrategy(PricingStrategy s){ this.ps=s; }
    double checkout(double base){ return ps.price(base); }
}
```

---

### 14) Observer
**Description.** Define one‑to‑many dependencies so that observers are notified automatically of state changes.  
**Use cases.** Event systems, GUIs, cache invalidation, reactive streams.  
**Benefits.** Decouples subject from observers; dynamic subscriptions.  
**Disadvantages.** Notification storms; ordering issues; memory leaks if not unsubscribed.

**Java**

```java
import java.util.*;
interface Observer { void onUpdate(int value); }
class Subject {
    private final List<Observer> obs=new ArrayList<>(); private int state=0;
    void subscribe(Observer o){ obs.add(o); }
    void setState(int s){ state=s; obs.forEach(o -> o.onUpdate(state)); }
}
class ConsoleObserver implements Observer { public void onUpdate(int v){ System.out.println("State="+v); } }
```

---

### 15) Command
**Description.** Encapsulate a request as an object (supports queueing, logging, undo/redo).  
**Use cases.** UI actions, task queues, transactional workflows.  
**Benefits.** Decouples invoker from receiver; macros; undo possible.  
**Disadvantages.** Many small command classes; state handling for undo.

**Java**

```java
import java.util.*;
interface Command { void execute(); }
class Light { void on(){ System.out.println("ON"); } void off(){ System.out.println("OFF"); } }
class OnCmd implements Command { private final Light l; OnCmd(Light l){ this.l=l; } public void execute(){ l.on(); } }
class OffCmd implements Command { private final Light l; OffCmd(Light l){ this.l=l; } public void execute(){ l.off(); } }
class Remote {
    private final Queue<Command> q = new ArrayDeque<>();
    void submit(Command c){ q.add(c); }
    void run(){ while(!q.isEmpty()) q.poll().execute(); }
}
```

---

### 16) Iterator
**Description.** Provide a standard way to traverse a collection without exposing its representation.  
**Use cases.** Custom collections; streaming; cursors.  
**Benefits.** Uniform traversal; hides data structure details.  
**Disadvantages.** External iterators can complicate concurrent modifications.

**Java**

```java
import java.util.*;
class Range implements Iterable<Integer> {
    private final int start, end;
    Range(int s,int e){ start=s; end=e; }
    public Iterator<Integer> iterator(){
        return new Iterator<Integer>(){
            int cur=start;
            public boolean hasNext(){ return cur<end; }
            public Integer next(){ return cur++; }
        };
    }
}
```

---

### 17) Mediator
**Description.** Encapsulate object interactions in a central mediator to reduce coupling.  
**Use cases.** Complex UI widgets coordination; chat rooms; air traffic control.  
**Benefits.** Simplifies communication; localizes interaction logic.  
**Disadvantages.** Mediator can become a god‑object; difficult to maintain if it grows too much.

**Java**

```java
class ChatRoom {
    void send(String from, String to, String msg){
        System.out.println(from + " -> " + to + ": " + msg);
    }
}
class User {
    private final String name; private final ChatRoom room;
    User(String n, ChatRoom r){ name=n; room=r; }
    void send(User to, String msg){ room.send(name, to.name, msg); }
}
```

---

### 18) Memento
**Description.** Capture an object’s internal state so it can be restored later.  
**Use cases.** Undo/redo, checkpoints, transactional savepoints.  
**Benefits.** Encapsulation preserved; easy revert.  
**Disadvantages.** Memory usage; care with deep copies and privacy.

**Java**

```java
class Editor {
    private String text = "";
    static class Memento { private final String state; Memento(String s){ state=s; } }
    Memento save(){ return new Memento(text); }
    void restore(Memento m){ this.text = m.state; }
    void type(String t){ text += t; }
    String content(){ return text; }
}
```

---

### 19) State
**Description.** Allow an object to alter its behavior when its internal state changes.  
**Use cases.** Media players, TCP connection states, workflows.  
**Benefits.** Removes conditional logic; localizes state behavior.  
**Disadvantages.** Extra classes; transitions must be managed.

**Java**

```java
interface PlayerState { void pressPlay(MediaPlayer ctx); }
class Playing implements PlayerState { public void pressPlay(MediaPlayer c){ System.out.println("Pause"); c.set(new Paused()); } }
class Paused  implements PlayerState { public void pressPlay(MediaPlayer c){ System.out.println("Play");  c.set(new Playing()); } }
class MediaPlayer {
    private PlayerState st = new Paused();
    void set(PlayerState s){ st=s; }
    void press(){ st.pressPlay(this); }
}
```

---

### 20) Template Method
**Description.** Define the **skeleton** of an algorithm in a base class; subclasses override specific steps.  
**Use cases.** Parsing pipelines; importers; algorithm families with fixed structure.  
**Benefits.** Code reuse; enforces order of steps.  
**Disadvantages.** Rigid structure; inheritance coupling.

**Java**

```java
abstract class DataImporter {
    public final void run(){ open(); parse(); close(); }
    protected void open(){ System.out.println("open"); }
    protected abstract void parse();
    protected void close(){ System.out.println("close"); }
}
class CsvImporter extends DataImporter { protected void parse(){ System.out.println("parse CSV"); } }
```

---

### 21) Visitor
**Description.** Represent operations to perform on elements of an **object structure** without changing the classes.  
**Use cases.** AST processing, serialization, metrics over object graphs.  
**Benefits.** Add new operations easily; separates concerns.  
**Disadvantages.** Hard to add new element types; double dispatch boilerplate.

**Java**

```java
interface Element { void accept(Visitor v); }
class Dot implements Element { public void accept(Visitor v){ v.visit(this); } }
class Circle implements Element { int r=5; public void accept(Visitor v){ v.visit(this); } }

interface Visitor { void visit(Dot d); void visit(Circle c); }
class AreaVisitor implements Visitor {
    public void visit(Dot d){ System.out.println("Dot area=0"); }
    public void visit(Circle c){ System.out.println("Circle area ~ " + (Math.PI*c.r*c.r)); }
}
```

---

### 22) Chain of Responsibility
**Description.** Pass a request along a chain of handlers; the first that can process it, does.  
**Use cases.** Middleware pipelines, validation chains, event bubbling.  
**Benefits.** Decouples sender from receiver; reorders/extends chain easily.  
**Disadvantages.** Hard to guarantee handling; debugging path can be tricky.

**Java**

```java
abstract class Handler {
    private Handler next;
    public Handler setNext(Handler n){ this.next=n; return n; }
    public void handle(String req){
        if(!process(req) && next!=null) next.handle(req);
    }
    protected abstract boolean process(String req);
}
class AuthHandler extends Handler { protected boolean process(String r){ if(r.contains("auth")){ System.out.println("auth ok"); return true; } return false; } }
class LoggingHandler extends Handler { protected boolean process(String r){ System.out.println("log:"+r); return false; } }
```

---

## Minimal Runnable Harness
Use this small `Main` to try multiple patterns quickly in one file.

```java
public class Main {
    public static void main(String[] args) {
        // Strategy quick demo
        PricingStrategy s = new HolidayDiscount();
        System.out.println(new Cart(s).checkout(100.0)); // 80.0

        // Observer quick demo
        Subject sub = new Subject();
        sub.subscribe(new ConsoleObserver());
        sub.setState(42);

        // Proxy quick demo
        Image img = new LazyImageProxy("poster.png");
        img.display(); // loads once
        img.display(); // cached
    }
}
```
