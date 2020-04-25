#pragma once

struct Vertex
{
  // Vertex position (Model Space) //

  /**
   * \brief x position in model space 
   */
  float x;

  /**
   * \brief y position in model space
   */
  float y;

  // Vertex Colors //

  /**
   * \brief red value for vertex color
   */
  float r;

  /**
   * \brief green value for vertex color
   */
  float g;

  /**
   * \brief blue value for vertex color 
   */
  float b;

  // UV Coordinates //

  /**
   * \brief x value in uv coordinates.
   */
  float uvx;

  /**
   * \brief y value in uv coordinates.
   */
  float uvy;
};
