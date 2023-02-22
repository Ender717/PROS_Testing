// Inclusion guard
#ifndef POSITION_H
#define POSITION_H

class Position
{
private:
    /**
     * The location of the position
     */
    double x;
    double y;
    double theta;

    /**
     * The velocity of the position
     */
    double xV;
    double yV;
    double thetaV;

public:
    /**
     * Parameterized constructor
     * @param _x The x-coordinate of the position
     * @param _y The y-coordinate of the position
     * @param _theta The angle of the position
     */
    Position(double _x, double _y, double _theta);

    /**
     * Parameterized constructor
     * @param _x The x-coordinate of the position
     * @param _y The y-coordinate of the position
     * @param _theta The angle of the position
     * @param _xV The x-velocity of the position
     * @param _yV The y-velocity of the position
     * @param _thetaV The angular velocity of the position
     */
    Position(double _x, double _y, double _theta, double _xV, double _yV, double _thetaV);

    /**
     * Gets the x-coordinate of the position
     * @return The x-coordinate of the position
     */
    double getX() const;

    /**
     * Gets the y-coordinate of the position
     * @return The y-coordinate of the position
     */
    double getY() const;

    /**
     * Gets the angle of the position
     * @return The angle of the position
     */
    double getTheta() const;

    /**
     * Gets the x-velocity of the position
     * @return The x-velocity of the position
     */
    double getXV() const;

    /**
     * Gets the y-velocity of the position
     * @return The y-velocity of the position
     */
    double getYV() const;

    /**
     * Gets the angular velocity of the position
     * @return The angular velocity of the position
     */
    double getThetaV() const;
};

#endif