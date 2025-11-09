#pragma once

#include <memory>
#include <typeinfo>

namespace objtran
{
    template <typename T>
    class object_transaction
    {
        private:
            bool committed = false;
            T* original_object;
            std::unique_ptr<T> copy_object;

        public:
            explicit object_transaction(T* obj)
            {
                original_object = obj;
                copy_object = std::make_unique<T>(*obj);
            }

            ~object_transaction()
            {
                commit();
            }

            // disable copy
            object_transaction(const object_transaction&) = delete;
            object_transaction& operator=(const object_transaction&) = delete;

            // disable move
            object_transaction(object_transaction&&) noexcept = default;
            object_transaction& operator=(object_transaction&&) noexcept = default;

        public:
            inline void rollback()
            {
                if (!committed && original_object && copy_object)
                    *original_object = *copy_object;
            }

            inline void commit()
            {
                committed = true;
                copy_object.reset();
            }

            inline bool is_committed() const noexcept
            {
                return committed;
            }
    };
}