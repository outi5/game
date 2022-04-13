#pragma once

// forward declaration
class Engine;

// Events are things that happen in the world (actors cannot do them
// directly) and will be processed to completion before actors take
// more turns. Useful for animations, enemies taking damage, etc.
class Event {
public:
    Event(int number_of_frames=1); // how many frames it should last
    virtual ~Event() {}
    void update();

    // returns whether event has finished
    virtual bool is_done() const;

    // what the event does per update frame
    virtual void execute(Engine& engine) = 0;

    // called when the even is completed, useful for cleaning up or
    // chaining together more actions (e.g. an attack animation leads
    // to a hit event)
    virtual void when_done(Engine& engine);

protected:
    int number_of_frames, frame_count;
};
