/***************************************************************************                                                                                     
*   Copyright 2012 Advanced Micro Devices, Inc.                                     
*                                                                                    
*   Licensed under the Apache License, Version 2.0 (the "License");   
*   you may not use this file except in compliance with the License.                 
*   You may obtain a copy of the License at                                          
*                                                                                    
*       http://www.apache.org/licenses/LICENSE-2.0                      
*                                                                                    
*   Unless required by applicable law or agreed to in writing, software              
*   distributed under the License is distributed on an "AS IS" BASIS,              
*   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.         
*   See the License for the specific language governing permissions and              
*   limitations under the License.                                                   

***************************************************************************/                                                                                     

#if !defined( REDUCE_BY_KEY_H )
#define REDUCE_BY_KEY_H
#pragma once

#include <bolt/cl/bolt.h>
#include <bolt/cl/functional.h>
#include <bolt/cl/device_vector.h>
#include <bolt/cl/pair.h>

/*! \file reduce_by_key.h
*/

namespace bolt
{
namespace cl
{

/*! \addtogroup algorithms
 */

/*! \addtogroup reductions
 *   \ingroup algorithms
 */ 

/*! \addtogroup reduce_by_key
 *   \ingroup reductions
 *   \{
 */

/*! \brief inclusive_scan_by_key performs, on a sequence,
 * an inclusive scan of each sub-sequence as defined by equivalent keys.
 *
 * \param first1        The first element of the key sequence.
 * \param last1         The last  element of the key sequence.
 * \param first2        The first element of the value sequence.
 * \param result        The first element of the output sequence.
 * \param binary_pred   Binary predicate which determines if two keys are equal.
 * \param binary_funct  Binary function for scanning transformed elements.
 * \param user_code     A user-specified string that is preppended to the generated OpenCL kernel.
 *
 * \tparam InputIterator1   is a model of Input Iterator.
 * \tparam InputIterator2   is a model of Input Iterator.
 * \tparam OutputIterator   is a model of Output Iterator.
 * \tparam BinaryPredicate  is a model of Binary Predicate.
 * \tparam BinaryFunction   is a model of Binary Function whose return type
 *                          is convertible to \c OutputIterator's  \c value_type.
 *
 * \return result+(last1-first1).
 *
 * \code
 * #include "bolt/cl/scan_by_key.h"
 * ...
 *
 * int keys[11] = { 7, 0, 0, 3, 3, 3, -5, -5, -5, -5, 3 };
 * int vals[11] = { 2, 2, 2, 2, 2, 2,  2,  2,  2,  2, 2 };
 * int out[11];
 *
 * bolt::cl::equal_to<int> eq;
 * bolt::cl::multiplies<int> mult;
 *
 * bolt::cl::inclusive_scan_by_key( keys, keys+11, vals, out, eq, mult );
 * // out => { 2, 2, 4, 2, 4, 8, 2, 4, 8, 16, 2 }
 *  \endcode
 *
 * \sa inclusive_scan
 * \sa http://www.sgi.com/tech/stl/partial_sum.html
 * \sa http://www.sgi.com/tech/stl/InputIterator.html
 * \sa http://www.sgi.com/tech/stl/OutputIterator.html
 * \sa http://www.sgi.com/tech/stl/BinaryPredicate.html
 * \sa http://www.sgi.com/tech/stl/BinaryFunction.html
 */
template<
    typename InputIterator1,
    typename InputIterator2,
    typename OutputIterator1,
    typename OutputIterator2,
    typename BinaryPredicate,
    typename BinaryFunction>
pair<OutputIterator1, OutputIterator2>
reduce_by_key(
    InputIterator1  keys_first,
    InputIterator1  keys_last,
    InputIterator2  values_first,
    OutputIterator1  keys_output,
    OutputIterator2  values_output,
    BinaryPredicate binary_pred,
    BinaryFunction binary_op,
    const std::string& user_code="" );

/*! \brief inclusive_scan_by_key performs, on a sequence,
 * an inclusive scan of each sub-sequence as defined by equivalent keys;
 * the BinaryFunction in this version is plus().
 *
 * \param first1        The first element of the key sequence.
 * \param last1         The last  element of the key sequence.
 * \param first2        The first element of the value sequence.
 * \param result        The first element of the output sequence.
 * \param binary_pred   Binary predicate which determines if two keys are equal.
 * \param user_code     A user-specified string that is preppended to the generated OpenCL kernel.
 *
 * \tparam InputIterator1   is a model of Input Iterator.
 * \tparam InputIterator2   is a model of Input Iterator.
 * \tparam OutputIterator   is a model of Output Iterator.
 * \tparam BinaryPredicate  is a model of Binary Predicate.
 *
 * \return result+(last1-first1).
 *
 * \code
 * #include "bolt/cl/scan_by_key.h"
 * ...
 *
 * int keys[11] = { 7, 0, 0, 3, 3, 3, -5, -5, -5, -5, 3 };
 * int vals[11] = { 1, 1, 1, 1, 1, 1,  1,  1,  1,  1, 1 };
 * int out[11];
 *
 * bolt::cl::equal_to<int> eq;
 *
 * bolt::cl::inclusive_scan_by_key( keys, keys+11, vals, out, eq );
 * // out => { 1, 1, 2, 1, 2, 3, 1, 2, 3, 4, 1 }
 *  \endcode
 *
 * \sa inclusive_scan
 * \sa http://www.sgi.com/tech/stl/partial_sum.html
 * \sa http://www.sgi.com/tech/stl/InputIterator.html
 * \sa http://www.sgi.com/tech/stl/OutputIterator.html
 * \sa http://www.sgi.com/tech/stl/BinaryPredicate.html
 * \sa http://www.sgi.com/tech/stl/BinaryFunction.html
 */
template<
    typename InputIterator1,
    typename InputIterator2,
    typename OutputIterator1,
    typename OutputIterator2,
    typename BinaryPredicate>
pair<OutputIterator1, OutputIterator2>
reduce_by_key(
    InputIterator1  keys_first,
    InputIterator1  keys_last,
    InputIterator2  values_first,
    OutputIterator1  keys_output,
    OutputIterator2  values_output,
    BinaryPredicate binary_pred,
    const std::string& user_code="" );

/*! \brief inclusive_scan_by_key performs, on a sequence,
 * an inclusive scan of each sub-sequence as defined by equivalent keys;
 * the BinaryFunction in this version is plus(), and the BinaryPredicate is equal_to().
 *
 * \param first1        The first element of the key sequence.
 * \param last1         The last  element of the key sequence.
 * \param first2        The first element of the value sequence.
 * \param result        The first element of the output sequence.
 * \param user_code     A user-specified string that is preppended to the generated OpenCL kernel.
 *
 * \tparam InputIterator1   is a model of Input Iterator.
 * \tparam InputIterator2   is a model of Input Iterator.
 * \tparam OutputIterator   is a model of Output Iterator.
 *
 * \return result+(last1-first1).
 *
 * \code
 * #include "bolt/cl/scan_by_key.h"
 * ...
 *
 * int keys[11] = { 7, 0, 0, 3, 3, 3, -5, -5, -5, -5, 3 };
 * int vals[11] = { 1, 1, 1, 1, 1, 1,  1,  1,  1,  1, 1 };
 * int out[11];
 *
 * bolt::cl::inclusive_scan_by_key( keys, keys+11, vals, out );
 * // out => { 1, 1, 2, 1, 2, 3, 1, 2, 3, 4, 1 }
 *  \endcode
 *
 * \sa inclusive_scan
 * \sa http://www.sgi.com/tech/stl/partial_sum.html
 * \sa http://www.sgi.com/tech/stl/InputIterator.html
 * \sa http://www.sgi.com/tech/stl/OutputIterator.html
 * \sa http://www.sgi.com/tech/stl/BinaryPredicate.html
 * \sa http://www.sgi.com/tech/stl/BinaryFunction.html
 */
template<
    typename InputIterator1,
    typename InputIterator2,
    typename OutputIterator1,
    typename OutputIterator2>
pair<OutputIterator1, OutputIterator2>
reduce_by_key(
    InputIterator1  keys_first,
    InputIterator1  keys_last,
    InputIterator2  values_first,
    OutputIterator1  keys_output,
    OutputIterator2  values_output,
    const std::string& user_code="" );

///////////////////////////// CTRL ////////////////////////////////////////////

/*! \brief inclusive_scan_by_key performs, on a sequence,
 * an inclusive scan of each sub-sequence as defined by equivalent keys.
 *
 * \param ctl           Control structure to control command-queue, debug, tuning, etc.  See bolt::cl::control.
 * \param first1        The first element of the key sequence.
 * \param last1         The last  element of the key sequence.
 * \param first2        The first element of the value sequence.
 * \param result        The first element of the output sequence.
 * \param binary_pred   Binary predicate which determines if two keys are equal.
 * \param binary_funct  Binary function for scanning transformed elements.
 * \param user_code     A user-specified string that is preppended to the generated OpenCL kernel.
 *
 * \tparam InputIterator1   is a model of Input Iterator.
 * \tparam InputIterator2   is a model of Input Iterator.
 * \tparam OutputIterator   is a model of Output Iterator.
 * \tparam BinaryPredicate  is a model of Binary Predicate.
 * \tparam BinaryFunction   is a model of Binary Function whose return type
 *                          is convertible to \c OutputIterator's  \c value_type.
 *
 * \return result+(last1-first1).
 *
 * \code
 * #include "bolt/cl/scan_by_key.h"
 * ...
 *
 * int keys[11] = { 7, 0, 0, 3, 3, 3, -5, -5, -5, -5, 3 };
 * int vals[11] = { 2, 2, 2, 2, 2, 2,  2,  2,  2,  2, 2 };
 * int out[11];
 *
 * bolt::cl::equal_to<int> eq;
 * bolt::cl::multiplies<int> mult;
 * bolt::cl::control ctrl = control::getDefault();
 *
 * bolt::cl::inclusive_scan_by_key( ctrl, keys, keys+11, vals, out, eq, mult );
 * // out => { 2, 2, 4, 2, 4, 8, 2, 4, 8, 16, 2 }
 *  \endcode
 *
 * \sa inclusive_scan
 * \sa http://www.sgi.com/tech/stl/partial_sum.html
 * \sa http://www.sgi.com/tech/stl/InputIterator.html
 * \sa http://www.sgi.com/tech/stl/OutputIterator.html
 * \sa http://www.sgi.com/tech/stl/BinaryPredicate.html
 * \sa http://www.sgi.com/tech/stl/BinaryFunction.html
 */
template<
    typename InputIterator1,
    typename InputIterator2,
    typename OutputIterator1,
    typename OutputIterator2,
    typename BinaryPredicate,
    typename BinaryFunction>
pair<OutputIterator1, OutputIterator2>
reduce_by_key(
    control &ctl,
    InputIterator1  keys_first,
    InputIterator1  keys_last,
    InputIterator2  values_first,
    OutputIterator1  keys_output,
    OutputIterator2  values_output,
    BinaryPredicate binary_pred,
    BinaryFunction binary_op,
    const std::string& user_code="" );

/*! \brief inclusive_scan_by_key performs, on a sequence,
 * an inclusive scan of each sub-sequence as defined by equivalent keys;
 * the BinaryFunction in this version is plus().
 *
 * \param ctl           Control structure to control command-queue, debug, tuning, etc.  See bolt::cl::control.
 * \param first1        The first element of the key sequence.
 * \param last1         The last  element of the key sequence.
 * \param first2        The first element of the value sequence.
 * \param result        The first element of the output sequence.
 * \param binary_pred   Binary predicate which determines if two keys are equal.
 * \param user_code     A user-specified string that is preppended to the generated OpenCL kernel.
 *
 * \tparam InputIterator1   is a model of Input Iterator.
 * \tparam InputIterator2   is a model of Input Iterator.
 * \tparam OutputIterator   is a model of Output Iterator.
 * \tparam BinaryPredicate  is a model of Binary Predicate.
 *
 * \return result+(last1-first1).
 *
 * \code
 * #include "bolt/cl/scan_by_key.h"
 * ...
 *
 * int keys[11] = { 7, 0, 0, 3, 3, 3, -5, -5, -5, -5, 3 };
 * int vals[11] = { 1, 1, 1, 1, 1, 1,  1,  1,  1,  1, 1 };
 * int out[11];
 *
 * bolt::cl::equal_to<int> eq;
 * bolt::cl::control ctrl = control::getDefault();
 *
 * bolt::cl::inclusive_scan_by_key( ctrl, keys, keys+11, vals, out, eq );
 * // out => { 1, 1, 2, 1, 2, 3, 1, 2, 3, 4, 1 }
 *  \endcode
 *
 * \sa inclusive_scan
 * \sa http://www.sgi.com/tech/stl/partial_sum.html
 * \sa http://www.sgi.com/tech/stl/InputIterator.html
 * \sa http://www.sgi.com/tech/stl/OutputIterator.html
 * \sa http://www.sgi.com/tech/stl/BinaryPredicate.html
 * \sa http://www.sgi.com/tech/stl/BinaryFunction.html
 */
template<
    typename InputIterator1,
    typename InputIterator2,
    typename OutputIterator1,
    typename OutputIterator2,
    typename BinaryPredicate>
pair<OutputIterator1, OutputIterator2>
reduce_by_key(
    control &ctl,
    InputIterator1  keys_first,
    InputIterator1  keys_last,
    InputIterator2  values_first,
    OutputIterator1  keys_output,
    OutputIterator2  values_output,
    BinaryPredicate binary_pred,
    const std::string& user_code="" );

/*! \brief inclusive_scan_by_key performs, on a sequence,
 * an inclusive scan of each sub-sequence as defined by equivalent keys;
 * the BinaryFunction in this version is plus(), and the BinaryPredicate is equal_to().
 *
 * \param ctl           Control structure to control command-queue, debug, tuning, etc.  See bolt::cl::control.
 * \param first1        The first element of the key sequence.
 * \param last1         The last  element of the key sequence.
 * \param first2        The first element of the value sequence.
 * \param result        The first element of the output sequence.
 * \param user_code     A user-specified string that is preppended to the generated OpenCL kernel.
 *
 * \tparam InputIterator1   is a model of Input Iterator.
 * \tparam InputIterator2   is a model of Input Iterator.
 * \tparam OutputIterator   is a model of Output Iterator.
 *
 * \return result+(last1-first1).
 *
 * \code
 * #include "bolt/cl/scan_by_key.h"
 * ...
 *
 * int keys[11] = { 7, 0, 0, 3, 3, 3, -5, -5, -5, -5, 3 };
 * int vals[11] = { 1, 1, 1, 1, 1, 1,  1,  1,  1,  1, 1 };
 * int out[11];
 *
 * bolt::cl::control ctrl = control::getDefault();
 *
 * bolt::cl::inclusive_scan_by_key( ctrl, keys, keys+11, vals, out );
 * // out => { 1, 1, 2, 1, 2, 3, 1, 2, 3, 4, 1 }
 *  \endcode
 *
 * \sa inclusive_scan
 * \sa http://www.sgi.com/tech/stl/partial_sum.html
 * \sa http://www.sgi.com/tech/stl/InputIterator.html
 * \sa http://www.sgi.com/tech/stl/OutputIterator.html
 * \sa http://www.sgi.com/tech/stl/BinaryPredicate.html
 * \sa http://www.sgi.com/tech/stl/BinaryFunction.html
 */
template<
    typename InputIterator1,
    typename InputIterator2,
    typename OutputIterator1,
    typename OutputIterator2>
pair<OutputIterator1, OutputIterator2>
reduce_by_key(
    control &ctl,
    InputIterator1  keys_first,
    InputIterator1  keys_last,
    InputIterator2  values_first,
    OutputIterator1  keys_output,
    OutputIterator2  values_output,
    const std::string& user_code="" );


/***********************************************************************************************************************
 * Exclusive Segmented Scan
 **********************************************************************************************************************/

/*! \brief exclusive_scan_by_key performs, on a sequence,
 * an exclusive scan of each sub-sequence as defined by equivalent keys.
 *
 * \param first1        The first element of the key sequence.
 * \param last1         The last  element of the key sequence.
 * \param first2        The first element of the value sequence.
 * \param result        The first element of the output sequence.
 * \param init          The value used to initialize the output scan sequence.
 * \param binary_pred   Binary predicate which determines if two keys are equal.
 * \param binary_funct  Binary function for scanning transformed elements.
 * \param user_code     A user-specified string that is preppended to the generated OpenCL kernel.
 *
 * \tparam InputIterator1   is a model of Input Iterator.
 * \tparam InputIterator2   is a model of Input Iterator.
 * \tparam OutputIterator   is a model of Output Iterator.
 * \tparam T                is convertible to \c OutputIterator's value_type.
 * \tparam BinaryPredicate  is a model of Binary Predicate.
 * \tparam BinaryFunction   is a model of Binary Function whose return type
 *                          is convertible to \c OutputIterator's  \c value_type.
 *
 * \return result+(last1-first1).
 *
 * \code
 * #include "bolt/cl/scan_by_key.h"
 * ...
 *
 * int keys[11] = { 7, 0, 0, 3, 3, 3, -5, -5, -5, -5, 3 };
 * int vals[11] = { 2, 2, 2, 2, 2, 2,  2,  2,  2,  2, 2 };
 * int out[11];
 *
 * bolt::cl::equal_to<int> eq;
 * bolt::cl::multiplies<int> mult;
 *
 * bolt::cl::exclusive_scan_by_key( keys, keys+11, vals, out, 1, eq, mult );
 * // out => { 1, 1, 2, 1, 2, 4, 1, 2, 4, 8, 1 }
 *  \endcode
 *
 * \sa exclusive_scan
 * \sa http://www.sgi.com/tech/stl/partial_sum.html
 * \sa http://www.sgi.com/tech/stl/InputIterator.html
 * \sa http://www.sgi.com/tech/stl/OutputIterator.html
 * \sa http://www.sgi.com/tech/stl/BinaryPredicate.html
 * \sa http://www.sgi.com/tech/stl/BinaryFunction.html
 */

}// end of bolt::cl namespace
}// end of bolt namespace

#include <bolt/cl/detail/reduce_by_key.inl>

#endif
