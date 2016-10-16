//
// Created by owt50 on 2016/9/29.
//

#ifndef _ATFRAME_SERVICE_COMPONENT_RANDOM_ENGINE_H
#define _ATFRAME_SERVICE_COMPONENT_RANDOM_ENGINE_H

#include <random/random_generator.h>

namespace util {
    class random_engine {
    private:
        random_engine();
        ~random_engine();

        static ::util::random::mt19937_64& _get_common_generator();
        static ::util::random::taus88& _get_fast_generator();
    public:
        /**
         * ʹ��ָ�����ӳ�ʼ�������������
         * @param [out] rnd Ҫ��ʼ����������
         * @param [in] seed ���������
         */
        template<typename RandomType>
        static void init_generator_with_seed(RandomType& rnd, typename RandomType::result_type seed) {
            rnd.init_seed(seed);
        }

        /**
         * ʹ��������ӳ�ʼ�������������
         * @param [out] rnd Ҫ��ʼ����������
         */
        template<typename RandomType>
        static void init_generator(RandomType& rnd) {
            init_generator_with_seed(rnd, static_cast<typename RandomType::result_type>(random()));
        }

        /**
         * ��׼�����
         * @return �����
         */
        static uint32_t random();

        /**
         * ��׼�������
         * @param [in] lowest ����
         * @param [in] highest ����
         * @return ��[lowest, highest) ֮��������
         */
        template<typename ResType>
        static ResType random_between(ResType lowest, ResType highest) {
            return _get_common_generator().random_between<ResType>(lowest, highest);
        }

        /**
         * ���������
         * @return �����
         */
        static uint32_t fast_random();

        /**
         * �����������
         * @param [in] lowest ����
         * @param [in] highest ����
         * @return ��[lowest, highest) ֮��������
         */
        template<typename ResType>
        static ResType fast_random_between(ResType lowest, ResType highest) {
            return _get_fast_generator().random_between<ResType>(lowest, highest);
        }
    };
}


#endif // _ATFRAME_SERVICE_COMPONENT_RANDOM_ENGINE_H
