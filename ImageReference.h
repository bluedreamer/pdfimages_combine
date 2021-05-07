#pragma once

#include <ostream>

class ImageReference
{
public:
   ImageReference() = default;

   /**
    * See Ref class from Object.h from poppler project.
    * @param object_number
    * @param generation_number
    */
   ImageReference(int object_number, int generation_number);

   /**
    *
    * @return The object number
    */
   [[nodiscard]] auto getObjectNumber() const -> int;

   /**
    *
    * @return The generation number
    */
   [[nodiscard]] auto getGenerationNumber() const -> int;

   friend auto operator==(const ImageReference &lhs, const ImageReference &rhs) -> bool;
   friend auto operator!=(const ImageReference &lhs, const ImageReference &rhs) -> bool;
   friend auto operator<(const ImageReference &lhs, const ImageReference &rhs) -> bool;
   friend auto operator<<(std::ostream &os, const ImageReference &rhs) -> std::ostream&;
private:
   int object_number_{-1};     //< Arbitrary int id of the viewiewable image on the page, could be multiple combined into one. ie the mask
                               // and the image would have the same id
   int generation_number_{-1}; //< Image generation  - guessing its version number of object ID
};

auto operator==(const ImageReference &lhs, const ImageReference &rhs) -> bool;
auto operator!=(const ImageReference &lhs, const ImageReference &rhs) -> bool;
auto operator<(const ImageReference &lhs, const ImageReference &rhs) -> bool;
auto operator<<(std::ostream &os, const ImageReference &rhs) -> std::ostream&;
