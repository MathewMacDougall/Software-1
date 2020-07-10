#pragma once

#include <Box2D/Box2D.h>

#include <optional>
#include <functional>
#include <queue>

#include "software/new_geom/point.h"
#include "software/new_geom/vector.h"
#include "software/world/ball_state.h"

class PhysicsWorld;

/**
 * This class represents a ball in a Box2D physics simulation. It provides a convenient
 * way for us to abstract the ball and convert to our own Ball class when data is needed.
 */
class PhysicsBall
{
   public:
    friend PhysicsWorld;

    /**
     * Creates a new PhysicsBall given a Box2D world and a Ball object. A Box2D body
     * representing the ball will be automatically added to the Box2D world and updated
     * during world update steps.
     *
     * @param world A shared_ptr to a Box2D World
     * @param ball_state The initial state of the ball
     * @param mass_kg The mass of the ball in kg
     * @param restitution The restitution of the ball
     * @param linear_damping The linear damping of the ball
     */
    explicit PhysicsBall(std::shared_ptr<b2World> world, const BallState& ball_state,
                         const double mass_kg, double restitution = 1.0,
                         double linear_damping = 0.0);

    PhysicsBall() = delete;

    // Delete the copy and assignment operators because copying this class causes
    // issues with the b2World and how it tracks bodies in the world, because as objects
    // are copied and destroyed, they will destroy the bodies in the b2World as well
    PhysicsBall& operator=(const PhysicsBall&) = delete;
    PhysicsBall(const PhysicsBall&)            = delete;

    /**
     * Destroys the PhysicsBall object and removes any corresponding bodies from
     * the physics world if the ball is part of one
     */
    ~PhysicsBall();

    /**
     * Returns the current state of the ball

     * @return The current state of the ball
     */
    BallState getBallState() const;

    /**
     * Returns the current position of the ball, in global field coordinates, in meters
     *
     * @return the current position of the ball, in global field coordinates, in meters
     */
    Point position() const;

    /**
     * Returns the current velocity of the ball, in global field coordinates, in m/s
     *
     * @return the current velocity of the ball, in global field coordinates, in m/s
     */
    Vector velocity() const;

    /**
     * Returns the momentum of the ball, in kg*m/s
     *
     * @return the momentum of the ball, in kg*m/s
     */
    Vector momentum() const;

    /**
     * Returns the mass of the ball in kg
     *
     * @return the mass of the ball in kg
     */
    float massKg() const;

    /**
     * Marks the ball as "in flight" until it has travelled the given distance
     * from its current location.
     *
     * @param in_flight_distance The distance for which the ball will be in flight
     */
    void setInFlightForDistance(double in_flight_distance);

    /**
     * Returns true if the ball is currently in flight, and false otherwise
     *
     * @return true if the ball is currently in flight, and false otherwise
     */
    bool isInFlight();

    /**
     * Applies the given force vector to the ball at its center of mass
     *
     * @param force The force to apply
     */
    void applyForce(const Vector& force);

    /**
     * Applies the given impulse vector to the ball at its center of mass
     *
     * @param force The impulse to apply
     */
    void applyImpulse(const Vector& impulse);

    /**
     * Sets the position of the PhysicsRobot to the given position. The robot
     * will maintain its orientation, but will have its linear and angular
     * velocity set to zero.
     *
     * @param position The new position of the robot
     */
    void setPosition(const Point &position, const Vector& velocity);

protected:
    /**
     * This functions runs any operations this PhysicsRobot wants to perform
     * after a physics step has happened. We assume this function will be called
     * by the PhysicsWorld at the correct time. This exists so that this class
     * doesn't accidentally make a change to the Box2D world in the middle of
     * a physics step, which causes the system to crash.
     */
    void runPostPhysicsStep();

   private:
    /**
     * Returns true if this ball is touching another object in the physics world
     *
     * @return true if the ball is touching another object in the physics world,
     * and false otherwise
     */
    bool isTouchingOtherObject() const;

    // See https://box2d.org/manual.pdf chapters 6 and 7 more information on Shapes,
    // Bodies, and Fixtures
    b2Body* ball_body;

    // If the ball is currently in flight, the in_flight_origin holds the point
    // where the ball initially became in flight
    std::optional<Point> in_flight_origin;
    double in_flight_distance_meters;
    // friction with other objects, such as robots/wall
    static constexpr double BALL_FRICTION = 0.0;

    // The restitution is the amount of energy retained when bouncing off walls and
    // robots, 0.0 means perfectly inelastic and 1.0 means perfectly elastic collision.
    // The linear damping determines how the linear motion of the ball decreases over
    // time, 0.0 means no damping and the damping increases as linear_damping increases.
    // Linear Damping link:
    // https://gamedev.stackexchange.com/questions/160047/what-does-lineardamping-mean-in-box2d
    const double ball_restitution;
    const double ball_linear_damping;

    std::queue<std::function<void()>> post_physics_step_functions;
};
